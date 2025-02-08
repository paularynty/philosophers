/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:40 by prynty            #+#    #+#             */
/*   Updated: 2025/02/08 17:23:01 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	time_to_stop(t_thread *thread)
{
	pthread_mutex_lock(&thread->philo->data_lock);
	if (thread->philo->dead_or_full)
		return (pthread_mutex_unlock(&thread->philo->data_lock), TRUE);
	return (pthread_mutex_unlock(&thread->philo->data_lock), FALSE);
}

static int	thread_stopper(t_philo *philo)
{
	size_t	i;

	i = 0;
	printf("do we go here at all\n");
	while (i < philo->philos_num)
	{
		pthread_mutex_lock(&philo->data_lock);
		if ((get_time() - philo->threads[i].prev_meal >= philo->time_to_die)
			|| philo->full_philos == philo->philos_num)
		{
			philo->dead_or_full = TRUE;
			printf("or here\n");
			if (philo->full_philos == philo->philos_num)
				printf("Every philosopher ate %ld times\n", philo->meals_eaten);
			else
				printf("%zu %zu died\n", get_time() - philo->start_time, i + 1);
			return (pthread_mutex_unlock(&philo->data_lock), TRUE);
		}
		i++;
		pthread_mutex_unlock(&philo->data_lock);
	}
	return (TRUE);
}

// void	simulation(void *ptr)
// {
// 	t_thread	*thread;

// 	thread = ptr;
// 	while (TRUE)
// 	{
// 		if (dead_check(thread))
// 			return (ptr);
// 		if (max_meal(thread))
// 			return (ptr);
// 	}
// 	return (ptr);
// }

void	stop_thread(t_philo *philo)
{
	while (TRUE)
	{
		if (thread_stopper(philo))
			break ;
	}
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
		i++;
	}
	return (TRUE);
}
