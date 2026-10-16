/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:32:26 by alexfuen          #+#    #+#             */
/*   Updated: 2026/02/19 20:32:28 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include "sys/time.h"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			meal_mutex;
	t_data					*data;
	pthread_t				thread_id;
	long					last_meal;
	unsigned int			philo_index;
	unsigned int			nb_meals;
}	t_philo;

typedef struct s_data
{
	long			nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_t		monitor_thread_id;
	unsigned int	nb_meals;
	unsigned int	end;
}	t_data;

void			*routine(void *arg);
void			*monitor(void *arg);
long			get_time(void);
long			my_atol(const char *nptr);
void			routine_loop(t_philo *philo_data);
void			wait_action(long delay, t_data *data);
unsigned int	init_args(char **argv, t_data **data);
unsigned int	is_end(t_data *data);
void			print_line(t_philo *philo_data, char *msg);
void			make_philo_action(t_philo *philo_data, int ind);

#endif
