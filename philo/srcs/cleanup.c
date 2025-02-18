/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:17:48 by prynty            #+#    #+#             */
/*   Updated: 2025/02/18 10:40:41 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	usage(void)
{
	printf("\n"PINK);
	printf("Usage ./philo philo_num die_time eat_time sleep_time meals_num\n");
	printf("\nArgument\tDescription\t\t\t\tMandatory?\tType\n"RESET);
	printf("philo_num\tnumber of philosophers\t\t\tyes\t\tunsigned number\n");
	printf("die_time\ttime to die\t\t\t\tyes\t\tunsigned number\n");
	printf("eat_time\ttime to eat\t\t\t\tyes\t\tunsigned number\n");
	printf("sleep_time\ttime to sleep\t\t\t\tyes\t\tunsigned number\n");
	printf("meals_num\ttimes each philosopher must eat\t\tno\t\tunsigned number\n");
	return (FALSE);
}

void	print_error(char *msg)
{
	printf(RED"Error\n"RESET);
	printf("%s\n", msg);
}

int	terminate_init(char *str, t_table *table, int destroy_prev_lock)
{
	size_t	i;

	if (str)
	{
		printf(RED"Error\n"RESET);
		printf("%s\n", str);
	}
	i = 0;
	while (i < table->philos_num)
		pthread_mutex_destroy(&table->forks[i++]);
	if (destroy_prev_lock)
		pthread_mutex_destroy(&table->data_lock);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	return (FALSE);
}

int	cleanup(char *str, t_table *table)
{
	size_t	i;

	if (str)
	{
		printf(RED"Error\n"RESET);
		printf("%s\n", str);
	}
	i = 0;
	while (i < table->philos_num)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->data_lock);
	pthread_mutex_destroy(&table->print_lock);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	return (FALSE);
}
