/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:33:18 by alexfuen          #+#    #+#             */
/*   Updated: 2026/02/19 20:33:22 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	manage_single(t_philo *philo_data)
{
	unsigned int	ind;

	while (1)
	{
		pthread_mutex_lock(&philo_data->data->data_mutex);
		ind = philo_data->data->end;
		pthread_mutex_unlock(&philo_data->data->data_mutex);
		if (!ind)
			usleep(1000);
		else
		{
			pthread_mutex_unlock(philo_data->right_fork);
			break ;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo_data;

	philo_data = (t_philo *)arg;
	if (philo_data->philo_index % 2
		|| (philo_data->philo_index % 2 == 0
			&& philo_data->philo_index == philo_data->data->nb_philos - 1))
	{
		make_philo_action(philo_data, 0);
		usleep(1000);
	}
	routine_loop(philo_data);
	if (philo_data->data->nb_philos == 1)
		manage_single(philo_data);
	return (NULL);
}
