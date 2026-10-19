/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:32:34 by alexfuen          #+#    #+#             */
/*   Updated: 2026/02/19 20:32:36 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	my_strlen(char *str)
{
	int	i;
	int	j;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '0')
		i++;
	j = 0;
	while (str[i + j])
		j++;
	return (j);
}

static unsigned int	is_numeric(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static unsigned int	parse_args(int argc, char **argv)
{
	unsigned int	i;

	i = 1;
	while (i < (unsigned int)argc - 1)
	{
		if (is_numeric(argv[i++]))
			return (1);
	}
	if (my_atol(argv[1]) < 1 || my_atol(argv[1]) > 200)
		return (1);
	if (my_strlen(argv[2]) >= 19
		|| my_strlen(argv[3]) >= 19
		|| my_strlen(argv[4]) >= 19)
		return (1);
	if (my_atol(argv[2]) < 60 || my_atol(argv[3]) < 60 || my_atol(argv[4]) < 60)
		return (1);
	if (argv[5])
	{
		if (my_atol(argv[5]) < 1 || my_atol(argv[5]) > 2147483647)
			return (1);
	}
	return (0);
}

static void	launch(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread_id, NULL,
			routine, &data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor_thread_id, NULL, monitor, data);
	pthread_join(data->monitor_thread_id, NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	free(data->philos);
	free(data->forks);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error : wrong number of arguments !\n", 36);
		return (1);
	}
	if (parse_args(argc, argv))
	{
		write(2, "Error : invalid argument !\n", 27);
		return (1);
	}
	if (init_args(argv, &data))
	{
		write(2, "Error : failed to allocate required memory !\n", 45);
		return (1);
	}
	launch(data);
	return (0);
}
