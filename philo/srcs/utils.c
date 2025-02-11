/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:18:52 by prynty            #+#    #+#             */
/*   Updated: 2025/02/11 14:45:48 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(char *msg, t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->print_lock);
	if (*philo->dead_or_full)
	{
		pthread_mutex_unlock(philo->print_lock);
		return (FALSE);
	}
	printf("%zu %zu %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->print_lock);
	return (TRUE);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(t_philo *philo, size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		pthread_mutex_lock(philo->death_lock);
		if (*(philo->dead_or_full))
		{
			pthread_mutex_unlock(philo->death_lock);
			return (FALSE);
		}
		pthread_mutex_unlock(philo->death_lock);
		usleep(100);
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
