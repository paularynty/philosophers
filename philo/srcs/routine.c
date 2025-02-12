/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:31:50 by prynty            #+#    #+#             */
/*   Updated: 2025/02/12 18:09:16 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating(t_thread *thread)
{
	if (thread->id % 2 == 0)
	{
		if (!lock_forks_even(thread))
			return (FALSE);
	}
	else
		if (!lock_forks_odd(thread))
			return (FALSE);
	pthread_mutex_lock(&thread->philo->data_lock);
	thread->meals_eaten++;
	thread->prev_meal = get_time();
	pthread_mutex_unlock(&thread->philo->data_lock);
	if (!print_message(EAT, thread))
	{
		unlock_forks(thread);
		return (FALSE);
	}
	pthread_mutex_lock(&thread->philo->data_lock);
	if (thread->meals_eaten == thread->philo->num_times_to_eat)
		thread->philo->full_philos++;
	pthread_mutex_unlock(&thread->philo->data_lock);
	ft_usleep(thread->philo->time_to_eat, thread->philo);
	unlock_forks(thread);
	return (TRUE);
}

static int	sleeping_thinking(t_thread *thread)
{
	if (!print_message(SLEEP, thread))
		return (FALSE);
	if (!ft_usleep(thread->philo->time_to_sleep + 1, thread->philo))
		return (FALSE);
	if (!print_message(THINK, thread))
		return (FALSE);
	return (TRUE);
}

void	*routine(void *ptr)
{
	t_thread	*thread;
	size_t		start_delay;

	thread = ptr;
	start_delay = 0;
	if (thread->philo->philos_num % 2 != 0)
		start_delay = (thread->philo->time_to_eat * 1000)
			* (thread->id - 1) / thread->philo->philos_num;
	print_message(THINK, thread);
	if (thread->id % 2 == 0)
		usleep(start_delay + (thread->philo->time_to_eat * 1000 / 2));
	else
		usleep(start_delay);
	while (!thread->philo->dead_or_full)
	{
		if (!eating(thread))
			break ;
		if (!sleeping_thinking(thread))
			break ;
	}
	return (ptr);
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
		usleep(1);
	}
	return (ptr);
}
