/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:23:16 by prynty            #+#    #+#             */
/*   Updated: 2025/01/31 16:30:49 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	init_mutexes(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->num_of_philos - 1)
		if (pthread_mutex_init(&philo->forks[i++], NULL) != 0)
			print_error("Error creating forks");
	if (pthread_mutex_init(&philo->lock, NULL) != 0)
	{
		i = 0;
		while (i < philo->num_of_philos - 1)
			pthread_mutex_destroy(&philo->forks[i++]);
	}
}

int	allocate_data(t_philo *philo)
{
	philo->threads = malloc(sizeof(t_thread) * philo->num_of_philos);
	if (!philo->threads)
		return (print_error("Failed to allocate threads"), FALSE);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philos);
	if (!philo->forks)
	{
		free(philo->threads);
		return (print_error("Failed to allocate forks"), FALSE);
	}
	return (TRUE);
}

int	init_data(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
	philo->start_time = get_time();
	if (!allocate_data(philo))
		return (FALSE);
	init_mutexes(philo);
	return (TRUE);
}
