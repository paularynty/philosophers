/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:31:50 by prynty            #+#    #+#             */
/*   Updated: 2025/02/18 10:39:23 by prynty           ###   ########.fr       */
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
		if (!lock_forks_odd(philo))
			return (FALSE);
	pthread_mutex_lock(&philo->table->data_lock);
	philo->meals_eaten++;
	philo->prev_meal = get_time();
	pthread_mutex_unlock(&philo->table->data_lock);
	if (!print_message(EAT, philo))
	{
		unlock_forks(philo);
		return (FALSE);
	}
	pthread_mutex_lock(&philo->table->data_lock);
	if (philo->meals_eaten == philo->table->num_times_to_eat)
		philo->table->full_philos++;
	pthread_mutex_unlock(&philo->table->data_lock);
	ft_usleep(philo->table->time_to_eat, philo->table);
	unlock_forks(philo);
	return (TRUE);
}

static int	sleeping_thinking(t_philo *philo)
{
	if (!print_message(SLEEP, philo))
		return (FALSE);
	if (!ft_usleep(philo->table->time_to_sleep + 1, philo->table))
		return (FALSE);
	if (!print_message(THINK, philo))
		return (FALSE);
	return (TRUE);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	size_t	start_delay;

	philo = ptr;
	start_delay = 0;
	if (philo->table->philos_num % 2 != 0)
		start_delay = (philo->table->time_to_eat * 1000)
			* (philo->id - 1) / philo->table->philos_num;
	print_message(THINK, philo);
	if (philo->id % 2 == 0)
		usleep(start_delay + (philo->table->time_to_eat * 1000 / 2));
	else
		usleep(start_delay);
	while (!philo->table->dead_or_full)
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
		pthread_mutex_lock(&table->data_lock);
		if (dead_or_full(table))
		{
			pthread_mutex_unlock(&table->data_lock);
			break ;
		}
		pthread_mutex_unlock(&table->data_lock);
		usleep(1);
	}
	return (ptr);
}
