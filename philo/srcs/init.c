/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:32:41 by alexfuen          #+#    #+#             */
/*   Updated: 2026/02/19 20:32:43 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	init_philos(t_data **data)
{
	unsigned int	i;

	i = 0;
	while (i < (*data)->nb_philos)
	{
		(*data)->philos[i].data = (*data);
		pthread_mutex_init(&(*data)->forks[i], NULL);
		pthread_mutex_init(&(*data)->philos[i].meal_mutex, NULL);
		(*data)->philos[i].left_fork = &(*data)->forks[i];
		(*data)->philos[i].nb_meals = 0;
		if (i == (*data)->nb_philos - 1)
			(*data)->philos[i].right_fork = &(*data)->forks[0];
		else
			(*data)->philos[i].right_fork = &(*data)->forks[i + 1];
		(*data)->philos[i].last_meal = (*data)->start_time;
		(*data)->philos[i].philo_index = i;
		i++;
	}
}

static void	init_values(t_data **data, char **argv)
{
	pthread_mutex_init(&(*data)->data_mutex, NULL);
	pthread_mutex_init(&(*data)->write_mutex, NULL);
	pthread_mutex_init(&(*data)->death_mutex, NULL);
	(*data)->time_to_die = my_atol(argv[2]);
	(*data)->time_to_eat = my_atol(argv[3]);
	(*data)->time_to_sleep = my_atol(argv[4]);
	(*data)->end = 0;
	(*data)->start_time = get_time();
	if (argv[5])
		(*data)->nb_meals = my_atol(argv[5]);
	else
		(*data)->nb_meals = -1;
}

static unsigned int	allocate_data(t_data **data, char **argv)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (1);
	(*data)->nb_philos = my_atol(argv[1]);
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->nb_philos);
	if (!(*data)->forks)
	{
		free(*data);
		return (1);
	}
	(*data)->philos = malloc(sizeof(t_philo) * (*data)->nb_philos);
	if (!(*data)->philos)
	{
		free((*data)->forks);
		free(*data);
		return (1);
	}
	return (0);
}

unsigned int	init_args(char **argv, t_data **data)
{
	if (allocate_data(data, argv))
		return (1);
	init_values(data, argv);
	init_philos(data);
	return (0);
}
