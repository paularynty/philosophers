/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:23:16 by prynty            #+#    #+#             */
/*   Updated: 2025/02/10 20:18:11 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	init_threads(t_table *table)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < table->philos_num)
// 	{
// 		table->threads[i].philo = philo;
// 		table->threads[i].meals_eaten = 0;
// 		table->threads[i].id = i + 1;
// 		table->threads[i].left_fork = &table->forks[i];
// 		table->threads[i].right_fork = &table->forks[(i + 1)
// 			% table->philos_num];
// 		table->threads[i++].prev_meal = table->start_time;
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
		|| pthread_mutex_init(&table->print_lock, NULL) != 0)
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
	table->threads = malloc(sizeof(t_thread *) * (philos_num + 1));
	if (!table->threads)
		return (NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * (philos_num + 1));
	if (!table->forks)
		return (NULL);
	if (!init_mutexes(table, philos_num))
		return (terminate(table, NULL, 0));
	return (table);
}

static int	init_philo(t_thread **thread, char **argv, size_t id)
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
	if ((*thread)->time_to_die == 0 ||(*thread)->time_to_eat == 0
		|| (*thread)->time_to_eat == 0 || (*thread)->num_times_to_eat == 0)
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
	(*table)->threads[index]->philos_num = last_index + 1;
	(*table)->threads[index]->dead_or_full = &(*table)->dead_or_full;
	(*table)->threads[index]->data_lock = &(*table)->data_lock;
	(*table)->threads[index]->print_lock = &(*table)->print_lock;
	(*table)->threads[index]->left_fork = &(*table)->forks[index];
	if (index == 0)
		(*table)->threads[index]->right_fork = &(*table)->forks[last_index];
	else
		(*table)->threads[index]->right_fork = &(*table)->forks[index - 1];
}

t_table	*init_data(char **argv)
{
	t_table	*table;
	size_t	philos_num;
	size_t	i;

	philos_num = ft_atol(argv[1]);
	i = 0;
	table = allocate_data(philos_num);
	if (!table)
		return (terminate(table, "Failed to allocate program data", i));
	while (i < philos_num)
	{
		table->threads[i] = malloc(sizeof(t_thread));
		if (!table->threads[i])
			return (terminate(table, "Failed to allocate thread memory", i));
		if (!init_philo(&table->threads[i], argv, i + 1))
			return (terminate(table, "Failed to initialize data", 0));
		connect_data(&table, i, (philos_num - 1));
		i++;
	}
	table->full_philos = 0;
	table->dead_or_full = FALSE;
	table->threads[philos_num] = NULL;
	return (table);
}
