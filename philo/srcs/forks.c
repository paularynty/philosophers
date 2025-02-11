/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:42:13 by prynty            #+#    #+#             */
/*   Updated: 2025/02/10 17:19:46 by prynty           ###   ########.fr       */
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
	{
		pthread_mutex_unlock(thread->right_fork);
		return (FALSE);
	}
	print_message(FORK, thread);
	pthread_mutex_lock(thread->left_fork);
	if (time_to_stop(thread))
	{
		unlock_forks_even(thread);
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
	if (thread->philos_num == 1)
	{
		ft_usleep(thread, thread->time_to_die);
		pthread_mutex_unlock(thread->left_fork);
		return (FALSE);
	}
	pthread_mutex_lock(thread->right_fork);
	if (time_to_stop(thread))
	{
		unlock_forks_odd(thread);
		return (FALSE);
	}
	print_message(FORK, thread);
	return (TRUE);
}
