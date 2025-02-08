/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:42:13 by prynty            #+#    #+#             */
/*   Updated: 2025/02/08 21:29:11 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks_even(t_thread *thread)
{
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
}

void	unlock_forks_odd(t_thread *thread)
{
	pthread_mutex_unlock(thread->right_fork);
	pthread_mutex_unlock(thread->left_fork);
}

int	lock_forks_even(t_thread *thread)
{
	pthread_mutex_lock(thread->right_fork);
	if (time_to_stop(thread))
		return (pthread_mutex_unlock(thread->right_fork), FALSE);
	print_message(FORK, thread);
	pthread_mutex_lock(thread->left_fork);
	if (time_to_stop(thread))
		return (unlock_forks_even(thread), FALSE);
	print_message(FORK, thread);
	return (TRUE);
}

int	lock_forks_odd(t_thread *thread)
{
	pthread_mutex_lock(thread->left_fork);
	if (time_to_stop(thread))
		return (pthread_mutex_unlock(thread->left_fork), FALSE);
	print_message(FORK, thread);
	if (thread->philo->philos_num == 1)
	{
		ft_usleep(thread->philo->time_to_die, thread->philo);
		return (pthread_mutex_unlock(thread->left_fork), FALSE);
	}
	pthread_mutex_lock(thread->right_fork);
	if (time_to_stop(thread))
		return (unlock_forks_odd(thread), FALSE);
	print_message(FORK, thread);
	return (TRUE);
}

