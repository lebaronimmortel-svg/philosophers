/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:32:49 by alexfuen          #+#    #+#             */
/*   Updated: 2026/02/19 20:32:51 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	unlock_all(t_philo *philo_data, unsigned int flag)
{
	pthread_mutex_unlock(&philo_data->data->death_mutex);
	if (flag)
		pthread_mutex_unlock(philo_data->right_fork);
	else
		pthread_mutex_unlock(philo_data->left_fork);
	if (flag)
		pthread_mutex_unlock(philo_data->left_fork);
	else
		pthread_mutex_unlock(philo_data->right_fork);
	pthread_mutex_unlock(&philo_data->data->data_mutex);
}

static void	eat_action(t_philo *philo_data, unsigned int flag)
{
	pthread_mutex_unlock(&philo_data->data->death_mutex);
	philo_data->last_meal = get_time();
	pthread_mutex_lock(&philo_data->meal_mutex);
	philo_data->nb_meals++;
	pthread_mutex_unlock(&philo_data->meal_mutex);
	pthread_mutex_unlock(&philo_data->data->data_mutex);
	print_line(philo_data, "is eating");
	wait_action(philo_data->data->time_to_eat, philo_data->data);
	if (flag)
		pthread_mutex_unlock(philo_data->right_fork);
	else
		pthread_mutex_unlock(philo_data->left_fork);
	if (flag)
		pthread_mutex_unlock(philo_data->left_fork);
	else
		pthread_mutex_unlock(philo_data->right_fork);
}

static void	make_eat(t_philo *philo_data, unsigned int flag)
{
	if (flag)
		pthread_mutex_lock(philo_data->left_fork);
	else
		pthread_mutex_lock(philo_data->right_fork);
	print_line(philo_data, "has taken a fork");
	if (philo_data->data->nb_philos == 1)
		return ;
	if (flag)
		pthread_mutex_lock(philo_data->right_fork);
	else
		pthread_mutex_lock(philo_data->left_fork);
	print_line(philo_data, "has taken a fork");
	pthread_mutex_lock(&philo_data->data->data_mutex);
	pthread_mutex_lock(&philo_data->data->death_mutex);
	if (philo_data->data->end)
	{
		unlock_all(philo_data, flag);
		return ;
	}
	else
		eat_action(philo_data, flag);
}

void	make_philo_action(t_philo *philo_data, int ind)
{
	if (ind)
	{
		print_line(philo_data, "is sleeping");
		wait_action(philo_data->data->time_to_sleep, philo_data->data);
	}
	else
	{
		print_line(philo_data, "is thinking");
		wait_action(1, philo_data->data);
	}
}

void	routine_loop(t_philo *philo_data)
{
	while (1)
	{
		if (is_end(philo_data->data))
			break ;
		if (philo_data->philo_index % 2)
			make_eat(philo_data, 1);
		else
			make_eat(philo_data, 0);
		if (philo_data->data->nb_philos != 1)
		{
			if (is_end(philo_data->data))
				break ;
			make_philo_action(philo_data, 1);
			if (is_end(philo_data->data))
				break ;
			make_philo_action(philo_data, 0);
			if (is_end(philo_data->data))
				break ;
		}
		else
			break ;
	}
}
