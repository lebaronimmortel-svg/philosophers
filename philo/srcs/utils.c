/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:32:56 by alexfuen          #+#    #+#             */
/*   Updated: 2026/02/19 20:33:01 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

long	my_atol(const char *nptr)
{
	int				sign;
	long			result;
	unsigned int	i;

	i = 0;
	while ((nptr[i] < 14 && nptr[i] > 8) || nptr[i] == 32)
		i++;
	sign = 1;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (sign * result);
}

unsigned int	is_end(t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	if (data->end)
	{
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_action(long delay, t_data *data)
{
	long	time;
	long	start;

	start = get_time();
	while (1)
	{
		time = get_time();
		pthread_mutex_lock(&data->data_mutex);
		if (data->end)
		{
			pthread_mutex_unlock(&data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->data_mutex);
		if (time - start >= delay)
			break ;
		usleep(1000);
	}
}

void	print_line(t_philo *philo_data, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo_data->data->death_mutex);
	if (!philo_data->data->end)
	{
		time = get_time();
		pthread_mutex_lock(&philo_data->data->write_mutex);
		printf("%lu %u %s\n", time - philo_data->data->start_time,
			philo_data->philo_index + 1, msg);
		pthread_mutex_unlock(&philo_data->data->write_mutex);
	}
	pthread_mutex_unlock(&philo_data->data->death_mutex);
}
