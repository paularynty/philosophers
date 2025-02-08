/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:31:50 by prynty            #+#    #+#             */
/*   Updated: 2025/02/08 20:59:44 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(char *msg, t_thread *thread)
{
	size_t	time;

	time = get_time() - thread->philo->start_time;
	pthread_mutex_lock(&thread->philo->print_lock);
	//add death lock
	if (thread->philo->dead_or_full)
	{
		pthread_mutex_unlock(&thread->philo->print_lock);
		return (FALSE);
	}
	printf("%zu %zu %s\n", time, thread->id, msg);
	pthread_mutex_unlock(&thread->philo->print_lock);
	return (TRUE);
}

static int	eating(t_thread *thread)
{
	if (thread->id % 2 == 0)
	{
		if (!lock_forks_even(thread))
			return (FALSE);
	}
	else
	{
		if (!lock_forks_odd(thread))
			return (FALSE);
	}
	pthread_mutex_lock(&thread->philo->data_lock);
	thread->philo->meals_eaten++;
	thread->prev_meal = get_time();
	pthread_mutex_unlock(&thread->philo->data_lock);
	if (!print_message(EAT, thread))
		return (FALSE);
	ft_usleep(thread->philo->time_to_eat, thread->philo);
	pthread_mutex_lock(&thread->philo->data_lock);
	if (thread->philo->meals_eaten == thread->philo->num_times_to_eat)
		thread->philo->full_philos++;
	pthread_mutex_unlock(&thread->philo->data_lock);
	if (thread->id % 2 == 0)
		return (unlock_forks_even(thread), TRUE);
	else
		return (unlock_forks_odd(thread), TRUE);
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

	thread = ptr;
	print_message(THINK, thread);
	if (thread->id % 2 == 0)
		ft_usleep(10, thread->philo);
	while (!thread->philo->dead_or_full)
	// while (!time_to_stop(thread))
	{
		// if (!forks(thread))
		// 	break ;
		if (!eating(thread))
			break ;
		if (!sleeping_thinking(thread))
			break ;
	}
	return (ptr);
}
