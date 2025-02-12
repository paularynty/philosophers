/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:17:48 by prynty            #+#    #+#             */
/*   Updated: 2025/02/12 13:04:17 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage(void)
{
	printf("\n"PINK);
	printf("Usage: ./philo philo_num die_time eat_time sleep_time meal_num\n");
	printf("\nArgument\tDescription\t\t\t\tMandatory?\tType\n"RESET);
	printf("philo_num\tnumber of philosophers\t\t\tyes\t\tunsigned number\n");
	printf("die_time\ttime to die\t\t\t\tyes\t\tunsigned number\n");
	printf("eat_time\ttime to eat\t\t\t\tyes\t\tunsigned number\n");
	printf("sleep_time\ttime to sleep\t\t\t\tyes\t\tunsigned number\n");
	printf("meals_num\ttimes each philosopher must eat\t\tno\t\tunsigned number\n");
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
	{
		printf(RED"Error\n"RESET);
		printf("%s\n", str);
	}
	i = 0;
	while (i < philo->philos_num)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data_lock);
	pthread_mutex_destroy(&philo->print_lock);
	free(philo->threads);
	free(philo->forks);
}
