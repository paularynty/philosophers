/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:23:16 by prynty            #+#    #+#             */
/*   Updated: 2025/02/18 10:37:44 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_num)
	{
		table->philos[i].table = table;
		table->philos[i].meals_eaten = 0;
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->philos_num];
		i++;
	}
}

static int	init_mutexes(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			print_error("Error initializing fork mutex");
			if (i > 0)
			{
				while (i >= 0)
					pthread_mutex_destroy(&table->forks[--i]);
			}
			free(table->forks);
			free(table->philos);
			return (FALSE);
		}
		i++;
	}
	if (pthread_mutex_init(&table->data_lock, NULL) != 0)
		return (terminate_init("Error initializing data mutex", table, FALSE));
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (terminate_init("Error initializing print mutex", table, TRUE));
	return (TRUE);
}

static int	allocate_data(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->philos_num);
	if (!table->philos)
	{
		print_error("Error allocating threads");
		return (FALSE);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philos_num);
	if (!table->forks)
	{
		print_error("Error allocating forks");
		free(table->philos);
		return (FALSE);
	}
	return (TRUE);
}

int	init_data(t_table *table, char **argv)
{
	table->philos_num = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->num_times_to_eat = ft_atol(argv[5]);
	else
		table->num_times_to_eat = -1;
	if (table->philos_num == 0 || table->time_to_die == 0
		|| table->time_to_eat == 0 || table->time_to_sleep == 0
		|| table->num_times_to_eat == 0)
		return (usage());
	table->dead_or_full = FALSE;
	table->full_philos = 0;
	table->sim_start = FALSE;
	table->start_time = get_time();
	if (!allocate_data(table))
		return (FALSE);
	if (!init_mutexes(table))
		return (FALSE);
	init_philos(table);
	return (TRUE);
}
