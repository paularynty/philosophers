/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:40 by prynty            #+#    #+#             */
/*   Updated: 2025/02/07 09:43:44 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	stop_thread(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->philos_num)
	{
		pthread_mutex_lock(&philo->data_lock);
		if ((get_time() - philo->threads[i].prev_meal >= philo->time_to_die)
			|| philo->full_philos == philo->philos_num)
		{
			philo->dead_or_full = TRUE;
			if (philo->full_philos == philo->philos_num)
				printf("Every philosopher ate %ld times\n", philo->meals_eaten);
			else
				printf("%zu %ld died\n", get_time() - philo->start_time, i + 1);
			return (pthread_mutex_unlock(&philo->data_lock), FALSE);
		}
		i++;
		pthread_mutex_unlock(&philo->data_lock);
	}
	return (TRUE);
}

int	join_thread(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->philos_num)
	{
		if (pthread_join(philo->threads[i].thread, NULL) != 0)
			return (terminate("Failed to join threads", philo), FALSE);
		i++;
	}
	return (TRUE);
}

int	create_thread(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->philos_num)
	{
		if (pthread_create(&(philo->threads[i].thread), NULL, &routine,
				&philo->threads[i]) != 0)
			return (terminate("Failed to create threads", philo), FALSE);
		printf("thread no: %zu\n", philo->threads[i].id);
		i++;
	}
	return (TRUE);
}
