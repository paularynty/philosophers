/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:31:50 by prynty            #+#    #+#             */
/*   Updated: 2025/02/04 13:32:45 by prynty           ###   ########.fr       */
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
	return (TRUE);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->lock);
	print_message(EAT, philo);
	return (TRUE);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (!print_message(THINK, philo))
		return (FALSE);
	pthread_mutex_unlock(&philo->lock);
	return (TRUE);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (!print_message(SLEEP, philo))
		return (FALSE);
	pthread_mutex_unlock(&philo->lock);
	return (TRUE);
}

void	*routine(void *ptr)
{
	t_thread	*threads;
	
	threads = ptr;
	if (threads->id % 2 == 0)
		ft_usleep(10, threads->philo);
    while (1)
    {
		eating(threads);
		sleeping(threads);
		thinking(threads);
	}
	return (ptr);
}
