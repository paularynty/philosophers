/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:40 by prynty            #+#    #+#             */
/*   Updated: 2025/02/12 15:40:05 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_stop(t_thread *thread)
{
	pthread_mutex_lock(&thread->philo->data_lock);
	if (thread->philo->dead_or_full)
	{	
		pthread_mutex_unlock(&thread->philo->data_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&thread->philo->data_lock);
	return (FALSE);
}

int	dead_or_full(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->philos_num)
	{
		if ((get_time() - philo->threads[i].prev_meal >= philo->time_to_die)
			|| philo->full_philos == philo->philos_num)
		{
			if (philo->full_philos == philo->philos_num)
			{
				philo->dead_or_full = TRUE;
				return (TRUE);
			}
			else
			{			
				print_message(DIED, &philo->threads[i]);
				philo->dead_or_full = TRUE;
				return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}

void	*monitoring(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (TRUE)
	{
		pthread_mutex_lock(&philo->data_lock);
		if (dead_or_full(philo))
		{
			pthread_mutex_unlock(&philo->data_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data_lock);
	}
	return (ptr);
}

int	join_thread(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->philos_num)
	{
		if (pthread_join(philo->threads[i].thread, NULL) != 0)
		{
			terminate("Failed to join threads", philo);
			return (FALSE);
		}
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
		{
			terminate("Failed to create threads", philo);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
