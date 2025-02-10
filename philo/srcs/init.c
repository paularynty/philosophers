/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:23:16 by prynty            #+#    #+#             */
/*   Updated: 2025/02/10 14:37:15 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (usage(), FALSE);
	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (usage(), FALSE);
		i++;
	}
	return (TRUE);
}

static void	init_threads(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->philos_num)
	{
		philo->threads[i].philo = philo;
		philo->threads[i].meals_eaten = 0;
		philo->threads[i].id = i + 1;
		philo->threads[i].left_fork = &philo->forks[i];
		philo->threads[i].right_fork = &philo->forks[(i + 1)
			% philo->philos_num];
		philo->threads[i++].prev_meal = philo->start_time;
	}
}

static void	init_mutexes(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->philos_num)
		if (pthread_mutex_init(&philo->forks[i++], NULL) != 0)
			print_error("Error creating forks");
	if (pthread_mutex_init(&philo->data_lock, NULL) != 0
		|| pthread_mutex_init(&philo->print_lock, NULL) != 0)
	{
		i = 0;
		while (i < philo->philos_num)
			pthread_mutex_destroy(&philo->forks[i++]);
	}
}

static int	allocate_data(t_philo *philo)
{
	philo->threads = malloc(sizeof(t_thread) * philo->philos_num);
	if (!philo->threads)
		return (print_error("Failed to allocate threads"), FALSE);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->philos_num);
	if (!philo->forks)
	{
		free(philo->threads);
		return (print_error("Failed to allocate forks"), FALSE);
	}
	return (TRUE);
}

int	init_data(t_philo *philo, char **argv)
{
	philo->philos_num = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atol(argv[5]);
	else
		philo->num_times_to_eat = -1;
	if (philo->philos_num == 0 || philo->time_to_die == 0
		|| philo->time_to_eat == 0 || philo->time_to_eat == 0
		|| philo->num_times_to_eat == 0)
		return (usage(), FALSE);
	philo->dead_or_full = FALSE;
	philo->full_philos = 0;
	philo->start_time = get_time();
	if (!allocate_data(philo))
		return (FALSE);
	init_mutexes(philo);
	init_threads(philo);
	return (TRUE);
}
