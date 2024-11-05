/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:13:19 by prynty            #+#    #+#             */
/*   Updated: 2024/11/05 18:51:42 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_error(char *msg)
{
	printf(RED"Error\n"RESET);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	terminate(char *str, t_program *program, pthread_mutex_t *forks)
{
	size_t	i;

	if (str)
		printf("%s\n", str);
	i = 0;
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->philos[0].num_of_philos)
		pthread_mutex_destroy(&forks[i++]);
	free(program->philos);
	program->philos = NULL;
}