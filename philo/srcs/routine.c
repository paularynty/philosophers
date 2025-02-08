/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:31:50 by prynty            #+#    #+#             */
/*   Updated: 2025/02/08 17:21:39 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	dead_philo(t_thread *thread)
{
	pthread_mutex_lock(&thread->philo->data_lock);
	if (thread->philo->dead_or_full)
		return (pthread_mutex_unlock(&thread->philo->data_lock), TRUE);
	return (pthread_mutex_unlock(&thread->philo->data_lock), FALSE);
}

static int	forks(t_thread *thread)
{
	if (time_to_stop(thread))
		return (FALSE);
	pthread_mutex_lock(thread->left_fork);
	if (!print_message(FORK, thread, thread->philo))
		return (pthread_mutex_unlock(thread->left_fork), FALSE);
	if (time_to_stop(thread) || thread->philo->philos_num == 1)
		return (pthread_mutex_unlock(thread->left_fork), FALSE);
	pthread_mutex_lock(thread->right_fork);
	if (!print_message(FORK, thread, thread->philo))
		return (pthread_mutex_unlock(thread->left_fork),
			pthread_mutex_unlock(thread->right_fork), FALSE);
	return (TRUE);
}

static int	eating(t_thread *thread)
{
	pthread_mutex_lock(&thread->philo->data_lock);
	thread->philo->meals_eaten++;
	thread->prev_meal = get_time();
	pthread_mutex_unlock(&thread->philo->data_lock);
	print_message(EAT, thread, thread->philo);
	ft_usleep(thread->philo->time_to_eat, thread->philo);
	pthread_mutex_lock(&thread->philo->data_lock);
	if (thread->philo->meals_eaten == thread->philo->num_times_to_eat)
		thread->philo->full_philos++;
	pthread_mutex_unlock(&thread->philo->data_lock);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	return (TRUE);
}

static int	sleeping_thinking(t_thread *thread)
{
	if (!print_message(SLEEP, thread, thread->philo))
		return (FALSE);
	if (!ft_usleep(thread->philo->time_to_sleep, thread->philo))
		return (FALSE);
	if (!print_message(THINK, thread, thread->philo))
		return (FALSE);
	return (TRUE);
}

void	*routine(void *ptr)
{
	t_thread	*thread;

	thread = ptr;
	if (thread->id % 2 == 0)
		ft_usleep(10, thread->philo);
	while (!dead_philo(thread))
	{
		if (!forks(thread))
			break ;
		eating(thread);
		if (!sleeping_thinking(thread))
			break ;
	}
	return (ptr);
}
