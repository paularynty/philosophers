/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:31:50 by prynty            #+#    #+#             */
/*   Updated: 2025/02/10 20:04:42 by prynty           ###   ########.fr       */
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
	{
		if (!lock_forks_odd(thread))
			return (FALSE);
	}
	pthread_mutex_lock(thread->data_lock);
	thread->meals_eaten++;
	thread->prev_meal = get_time();
	if (thread->meals_eaten == thread->num_times_to_eat)
		thread->full_philos++;
	pthread_mutex_unlock(thread->data_lock);
	if (!print_message(EAT, thread))
		return (FALSE);
	ft_usleep(thread, thread->time_to_eat);
	if (thread->id % 2 == 0)
		return (unlock_forks_even(thread), TRUE);
	else
		return (unlock_forks_odd(thread), TRUE);
}

static int	sleeping_thinking(t_thread *thread)
{
	if (!print_message(SLEEP, thread))
		return (FALSE);
	if (!ft_usleep(thread, thread->time_to_sleep + 1))
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
		ft_usleep(thread, 50);
	while (!thread->dead_or_full)
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
	t_table	*table;

	table = ptr;
	while (TRUE)
	{
		// if (table->dead_or_full)
		if (dead_or_full(table))
			break ;
	}
	return (ptr);
}
