/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:40 by prynty            #+#    #+#             */
/*   Updated: 2025/02/18 10:36:07 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->data_lock);
	if (philo->table->dead_or_full)
	{	
		pthread_mutex_unlock(&philo->table->data_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->table->data_lock);
	return (FALSE);
}

int	dead_or_full(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_num)
	{
		if ((get_time() - table->philos[i].prev_meal >= table->time_to_die)
			|| table->full_philos == table->philos_num)
		{
			if (table->full_philos == table->philos_num)
			{
				table->dead_or_full = TRUE;
				return (TRUE);
			}
			else
			{			
				print_message(DIED, &table->philos[i]);
				table->dead_or_full = TRUE;
				return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}

int	join_thread(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_num)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (cleanup("Failed to join threads", table));
		i++;
	}
	return (TRUE);
}

void	*sync_threads(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (TRUE)
	{
		pthread_mutex_lock(&philo->table->data_lock);
		if (philo->table->sim_start)
		{
			pthread_mutex_unlock(&philo->table->data_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->data_lock);
		usleep(1);
	}
	routine(philo);
	return (ptr);
}

int	create_thread(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_num)
	{
		if (pthread_create(&(table->philos[i].thread), NULL, &sync_threads,
				&table->philos[i]) != 0)
		{
			if (i > 0)
			{
				while (i >= 0)
					pthread_join(table->philos[--i].thread, NULL);
			}
			return (cleanup("Failed to create threads", table));
		}
		i++;
	}
	pthread_mutex_lock(&table->data_lock);
	table->start_time = get_time();
	i = 0;
	while (i < table->philos_num)
		table->philos[i++].prev_meal = table->start_time;
	table->sim_start = TRUE;
	pthread_mutex_unlock(&table->data_lock);
	return (TRUE);
}
