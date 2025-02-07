/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:31:50 by prynty            #+#    #+#             */
/*   Updated: 2025/02/07 09:41:53 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	death(t_thread *thread)
{
	print_message(DIED, thread->philo);
	terminate(NULL, thread->philo);
}

static int	forks(t_thread *thread)
{
	pthread_mutex_lock(thread->l_fork);
	if (!print_message(LFORK, thread->philo))
		return (pthread_mutex_unlock(thread->l_fork), FALSE);
	if (thread->philo->philos_num == 1)
		return (pthread_mutex_unlock(thread->l_fork), FALSE);
	pthread_mutex_lock(thread->r_fork);
	if (!print_message(RFORK, thread->philo))
			return (pthread_mutex_unlock(thread->l_fork), 
				pthread_mutex_unlock(thread->r_fork), FALSE);
	return (TRUE);
}

static int	eating(t_thread *thread)
{
	pthread_mutex_lock(&thread->philo->data_lock);
	thread->philo->meals_eaten++;
	thread->prev_meal = get_time();
	pthread_mutex_unlock(&thread->philo->data_lock);
	print_message(EAT, thread->philo);
	ft_usleep(thread->philo->time_to_eat, thread->philo);
	if (thread->philo->meals_eaten == thread->philo->num_times_to_eat)
		thread->philo->full_philos++;
	pthread_mutex_unlock(thread->l_fork);
	pthread_mutex_unlock(thread->r_fork);
	return (TRUE);
}

static int	sleeping_thinking(t_thread *thread)
{
	if (!print_message(SLEEP, thread->philo))
		return (FALSE);
	if (!ft_usleep(thread->philo->time_to_sleep, thread->philo))
		return (FALSE);
	if (!print_message(THINK, thread->philo))
		return (FALSE);
	return (TRUE);
}

void	*routine(void *ptr)
{
	t_thread	*thread;
	
	thread = ptr;
	if (thread->id % 2 == 0)
		ft_usleep(10, thread->philo);
    while (1)
    {
		if (!forks(thread))
			break ;
		eating(thread);
		if (!sleeping_thinking(thread))
			break ;
	}
	return (ptr);
}
