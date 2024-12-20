/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:17:48 by prynty            #+#    #+#             */
/*   Updated: 2024/11/06 18:56:14 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_error(char *msg)
{
	printf(RED"Error\n"RESET);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	terminate(char *str, t_philo *philo)
{
	size_t	i;

	if (str)
		printf("%s\n", str);
	i = 0;
	while (i < philo->num_of_philos)
		pthread_mutex_destroy(&philo->forks[i++]);
	pthread_mutex_destroy(philo->lock);
	free(philo->threads);
	free(philo->forks);
}
