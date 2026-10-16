/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:33:10 by alexfuen          #+#    #+#             */
/*   Updated: 2026/02/19 20:33:12 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static unsigned int	check_death(t_data *data, unsigned int i, long time)
{
	unsigned int	ind;

	ind = 0;
	pthread_mutex_lock(&data->data_mutex);
	if (time - data->philos[i].last_meal > data->time_to_die)
	{
		print_line(&data->philos[i], "died");
		ind = 1;
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (ind);
}

static void	stop(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
		pthread_join(data->philos[i++].thread_id, NULL);
}

static void	update_end(t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	pthread_mutex_lock(&data->death_mutex);
	data->end = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->data_mutex);
}

unsigned int	loop(t_data *data)
{
	long			time;
	unsigned int	i;
	unsigned int	flag;
	unsigned int	ind;

	flag = 1;
	time = get_time();
	i = 0;
	while (i < data->nb_philos)
	{
		ind = check_death(data, i, time);
		if (ind)
			break ;
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].nb_meals < data->nb_meals)
			flag = 0;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	if (!ind)
		ind = flag;
	return (ind);
}

void	*monitor(void *arg)
{
	t_data			*data;
	unsigned int	flag;

	data = (t_data *)arg;
	while (1)
	{
		flag = loop(data);
		if (flag)
		{
			update_end(data);
			break ;
		}
		usleep(1000);
	}
	stop(data);
	return (NULL);
}
