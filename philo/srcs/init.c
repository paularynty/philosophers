/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:23:16 by prynty            #+#    #+#             */
/*   Updated: 2025/02/11 16:15:08 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	init_philos(t_table *table)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < table->philos_num)
// 	{
// 		table->philos[i].philo = philo;
// 		table->philos[i].meals_eaten = 0;
// 		table->philos[i].id = i + 1;
// 		table->philos[i].left_fork = &table->forks[i];
// 		table->philos[i].right_fork = &table->forks[(i + 1)
// 			% table->philos_num];
// 		table->philos[i++].prev_meal = table->start_time;
// 	}
// }

static int	init_mutexes(t_table *table, size_t philos_num)
{
	size_t	i;

	i = 0;
	while (i < philos_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			print_error("Error creating forks");
			return (FALSE);
		}
		i++;
	}
	if (pthread_mutex_init(&table->data_lock, NULL) != 0
		|| pthread_mutex_init(&table->print_lock, NULL) != 0
		|| pthread_mutex_init(&table->death_lock, NULL) != 0)
	{
		print_error("Error initializing mutexes");
		return (FALSE);
	}
	return (TRUE);
}

static t_table	*allocate_data(size_t philos_num)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philos = malloc(sizeof(t_philo *) * (philos_num + 1));
	if (!table->philos)
		return (NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * (philos_num + 1));
	if (!table->forks)
		return (NULL);
	if (!init_mutexes(table, philos_num))
		return (terminate(table, NULL, 0));
	return (table);
}

static int	init_philo(t_philo **thread, char **argv, size_t id)
{
	size_t	time;

	(*thread)->id = id;
	(*thread)->time_to_die = ft_atol(argv[2]);
	(*thread)->time_to_eat = ft_atol(argv[3]);
	(*thread)->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		(*thread)->num_times_to_eat = ft_atol(argv[5]);
	else
		(*thread)->num_times_to_eat = -1;
	if ((*thread)->time_to_die == 0 || (*thread)->time_to_eat == 0
		|| (*thread)->time_to_sleep == 0 || (*thread)->num_times_to_eat == 0)
	{
		print_usage();
		return (FALSE);
	}
	(*thread)->meals_eaten = 0;
	time = get_time();
	(*thread)->start_time = time;
	(*thread)->prev_meal = time;
	return (TRUE);
}

void	connect_data(t_table **table, size_t index, size_t last_index)
{
	(*table)->philos[index]->philos_num = last_index + 1;
	(*table)->philos[index]->dead_or_full = &(*table)->dead_or_full;
	(*table)->philos[index]->full_philos = &(*table)->full_philos;
	(*table)->philos[index]->data_lock = &(*table)->data_lock;
	(*table)->philos[index]->print_lock = &(*table)->print_lock;
	(*table)->philos[index]->death_lock = &(*table)->death_lock;
	(*table)->philos[index]->left_fork = &(*table)->forks[index];
	if (index == 0)
		(*table)->philos[index]->right_fork = &(*table)->forks[last_index];
	else
		(*table)->philos[index]->right_fork = &(*table)->forks[index - 1];
}

t_table	*init_data(char **argv)
{
	t_table	*table;
	size_t	philos_num;
	size_t	i;

	philos_num = ft_atol(argv[1]);
	if (philos_num == 0)
		return (NULL);
	i = 0;
	table = allocate_data(philos_num);
	if (!table)
		return (terminate(table, "Failed to allocate program data", i));
	while (i < philos_num)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
			return (terminate(table, "Failed to allocate thread memory", i));
		if (!init_philo(&table->philos[i], argv, i + 1))
			return (terminate(table, "Failed to initialize data", 0));
		connect_data(&table, i, (philos_num - 1));
		i++;
	}
	table->full_philos = 0;
	table->dead_or_full = FALSE;
	table->philos[philos_num] = NULL;
	return (table);
}
