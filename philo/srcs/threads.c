/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:40 by prynty            #+#    #+#             */
/*   Updated: 2025/02/11 14:28:22 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->data_lock);
	if (*philo->dead_or_full)
	{
		pthread_mutex_unlock(philo->data_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->data_lock);
	return (FALSE);
}

int	dead_or_full(t_table *table)
{
	size_t	i;

	i = 0;
	while (table->philos[i])
	{
		pthread_mutex_lock(table->philos[i]->data_lock);
		if ((get_time() - table->philos[i]->prev_meal >= table->philos[0]->time_to_die)
			|| table->full_philos == table->philos[0]->philos_num)
		{
			if (table->full_philos == table->philos[0]->philos_num)
			{
				table->dead_or_full = TRUE;
				return (pthread_mutex_unlock(table->philos[i]->data_lock), TRUE);
			}
			else
			{
				print_message(DIED, table->philos[i]);
				table->dead_or_full = TRUE;
				return (pthread_mutex_unlock(table->philos[i]->data_lock), TRUE);
			}
		}
		pthread_mutex_unlock(table->philos[i]->data_lock);
		i++;
	}
	return (FALSE);
}

int	join_thread(t_table *table)
{
	size_t	i;

	i = 0;
	while (table->philos[i])
	{
		if (pthread_join(table->philos[i]->thread, NULL) != 0)
		{
			terminate(table, "Failed to join philos", 0);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	create_thread(t_table *table)
{
	size_t	i;

	i = 0;
	while (table->philos[i])
	{
		if (pthread_create(&table->philos[i]->thread, NULL, &routine,
				table->philos[i]) != 0)
		{		
			terminate(table, "Failed to create threads", 0);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
