/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:42:13 by prynty            #+#    #+#             */
/*   Updated: 2025/02/12 15:41:58 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_thread *thread)
{
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
}

int	lock_forks_even(t_thread *thread)
{
	pthread_mutex_lock(thread->right_fork);
	if (time_to_stop(thread))
	{
		pthread_mutex_unlock(thread->right_fork);
		return (FALSE);
	}
	print_message(FORK, thread);
	pthread_mutex_lock(thread->left_fork);
	if (time_to_stop(thread))
	{
		unlock_forks(thread);
		return (FALSE);
	}
	print_message(FORK, thread);
	return (TRUE);
}

int	lock_forks_odd(t_thread *thread)
{
	pthread_mutex_lock(thread->left_fork);
	if (time_to_stop(thread))
	{
		pthread_mutex_unlock(thread->left_fork);
		return (FALSE);
	}
	print_message(FORK, thread);
	if (thread->philo->philos_num == 1)
	{
		ft_usleep(thread->philo->time_to_die, thread->philo);
		pthread_mutex_unlock(thread->left_fork);
		return (FALSE);
	}
	pthread_mutex_lock(thread->right_fork);
	if (time_to_stop(thread))
	{
		unlock_forks(thread);
		return (FALSE);
	}
	print_message(FORK, thread);
	return (TRUE);
}
