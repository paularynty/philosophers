/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:18:52 by prynty            #+#    #+#             */
/*   Updated: 2025/02/10 19:47:14 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(char *msg, t_thread *thread)
{
	size_t	time;

	time = get_time() - thread->start_time;
	pthread_mutex_lock(thread->print_lock);
	//add death lock
	if (thread->dead_or_full)
	{
		pthread_mutex_unlock(thread->print_lock);
		return (FALSE);
	}
	printf("%zu %zu %s\n", time, thread->id, msg);
	pthread_mutex_unlock(thread->print_lock);
	return (TRUE);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(t_thread *thread, size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (thread->dead_or_full)
			return (FALSE);
		usleep(500);
	}
	return (TRUE);
}

size_t	ft_atol(char *str)
{
	size_t	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return ((size_t)(result));
}
