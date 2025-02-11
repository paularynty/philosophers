/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:31:50 by prynty            #+#    #+#             */
/*   Updated: 2025/02/11 14:27:51 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!lock_forks_even(philo))
			return (FALSE);
	}
	else
	{
		if (!lock_forks_odd(philo))
			return (FALSE);
	}
	pthread_mutex_lock(philo->data_lock);
	philo->meals_eaten++;
	philo->prev_meal = get_time();
	if (philo->meals_eaten == philo->num_times_to_eat)
		(*philo->full_philos)++;
	pthread_mutex_unlock(philo->data_lock);
	if (!print_message(EAT, philo))
		return (FALSE);
	ft_usleep(philo, philo->time_to_eat);
	if (philo->id % 2 == 0)
		return (unlock_forks_even(philo), TRUE);
	else
		return (unlock_forks_odd(philo), TRUE);
}

static int	sleeping_thinking(t_philo *philo)
{
	if (!print_message(SLEEP, philo))
		return (FALSE);
	if (!ft_usleep(philo, philo->time_to_sleep + 1))
		return (FALSE);
	if (!print_message(THINK, philo))
		return (FALSE);
	return (TRUE);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	print_message(THINK, philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo, 50);
	while (!*philo->dead_or_full)
	{
		if (!eating(philo))
			break ;
		if (!sleeping_thinking(philo))
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
		if (dead_or_full(table))
			break ;
		usleep(500);
	}
	return (ptr);
}
