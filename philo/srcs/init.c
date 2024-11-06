/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:23:16 by prynty            #+#    #+#             */
/*   Updated: 2024/11/06 19:31:38 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_forks(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->num_of_philos)
		if (pthread_mutex_init(&philo->forks[i++], NULL) != 0)
			print_error("Error creating forks");
}

void	init_struct(t_philo *philo, char **argv)
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
	// if (philo->num_of_philo > PHILO_MAX)
	// 	print_error("Too many philoophers");
}
