/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:17:48 by prynty            #+#    #+#             */
/*   Updated: 2025/02/04 13:20:30 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	usage(void)
{
	printf("\n"PINK);
	printf("Usage: ./philo philo_num die_time eat_time sleep_time meal_num\n");
	printf("\nArgument	Description			Mandatory?	Type\n"RESET);
	printf("philo_num	number of philosophers		yes		unsigned\n");
	printf("die_time	time to die			yes		unsigned\n");
	printf("eat_time	time to eat			yes		unsigned\n");
	printf("sleep_time	time to sleep			yes		unsigned\n");
	printf("meals_num	times each philosopher must eat	no		unsigned\n");
}

void	print_error(char *msg)
{
	printf(RED"Error\n"RESET);
	printf("%s\n", msg);
}

void	terminate(char *str, t_philo *philo)
{
	size_t	i;

	if (str)
		printf("%s\n", str);
	i = 0;
	while (i < philo->num_of_philos)
		pthread_mutex_destroy(&philo->forks[i++]);
	pthread_mutex_destroy(&philo->lock);
	free(philo->threads);
	free(philo->forks);
}
