/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:31:50 by prynty            #+#    #+#             */
/*   Updated: 2024/11/06 19:33:02 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	death(t_philo *philo)
{
	print_message(DIED, philo);
	terminate(NULL, philo);
}

int	forks(t_philo *philo)
{
	pthread_mutex_lock(philo->threads->l_fork);
	print_message(LFORK, philo);
	pthread_mutex_lock(philo->threads->r_fork);
	print_message(RFORK, philo);
	return (SUCCESS);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->lock);
	print_message(EAT, philo);
	return (SUCCESS);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (!print_message(THINK, philo))
		return (FAILURE);
	pthread_mutex_unlock(philo->lock);
	return (SUCCESS);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (!print_message(SLEEP, philo))
		return (FAILURE);
	pthread_mutex_unlock(philo->lock);
	return (SUCCESS);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	
    while (1)
    {
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (ptr);
}
