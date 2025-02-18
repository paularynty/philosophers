/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:42:13 by prynty            #+#    #+#             */
/*   Updated: 2025/02/18 10:34:28 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	lock_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (time_to_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (FALSE);
	}
	print_message(FORK, philo);
	pthread_mutex_lock(philo->left_fork);
	if (time_to_stop(philo))
	{
		unlock_forks(philo);
		return (FALSE);
	}
	print_message(FORK, philo);
	return (TRUE);
}

int	lock_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (time_to_stop(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (FALSE);
	}
	print_message(FORK, philo);
	if (philo->table->philos_num == 1)
	{
		ft_usleep(philo->table->time_to_die, philo->table);
		pthread_mutex_unlock(philo->left_fork);
		return (FALSE);
	}
	pthread_mutex_lock(philo->right_fork);
	if (time_to_stop(philo))
	{
		unlock_forks(philo);
		return (FALSE);
	}
	print_message(FORK, philo);
	return (TRUE);
}
