/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:18:52 by prynty            #+#    #+#             */
/*   Updated: 2024/11/06 19:30:59 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_message(char *msg, t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->lock);
	// if (!dead_philo(philo))
	printf("%zu %d %s\n", time, philo->threads->id, msg);
	pthread_mutex_unlock(philo->lock);
	return (SUCCESS);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_digit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

size_t	ft_atoi(char *str)
{
	long	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return ((size_t)(result));
}
