/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:40 by prynty            #+#    #+#             */
/*   Updated: 2025/02/10 20:14:30 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_stop(t_thread *thread)
{
	pthread_mutex_lock(thread->data_lock);
	if (thread->dead_or_full)
	{
		pthread_mutex_unlock(thread->data_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(thread->data_lock);
	return (FALSE);
}

int	dead_or_full(t_table *table)
{
	size_t	i;

	i = 0;
	while (table->threads[i])
	{
		pthread_mutex_lock(&table->data_lock);
		if ((get_time() - table->threads[i]->prev_meal >= table->threads[i]->time_to_die)
			|| table->full_philos == table->threads[i]->philos_num)
		{
			if (table->full_philos == table->threads[i]->philos_num)
			{
				table->dead_or_full = TRUE;
				pthread_mutex_unlock(&table->data_lock);
				return (TRUE);
			}
			else
			{
				printf("%zu\n", table->threads[i]->prev_meal);
				print_message(DIED, table->threads[i]);
				table->dead_or_full = TRUE;
				pthread_mutex_unlock(&table->data_lock);
				return (TRUE);
			}
		}
		i++;
		pthread_mutex_unlock(&table->data_lock);
	}
	return (FALSE);
}

int	join_thread(t_table *table)
{
	size_t	i;

	i = 0;
	while (table->threads[i])
	{
		if (pthread_join(table->threads[i]->thread, NULL) != 0)
		{
			terminate(table, "Failed to join threads", 0);
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
	while (table->threads[i])
	{
		if (pthread_create(&table->threads[i]->thread, NULL, &routine,
				table->threads[i]) != 0)
		{		
			terminate(table, "Failed to create threads", 0);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
