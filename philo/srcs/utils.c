/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:18:52 by prynty            #+#    #+#             */
/*   Updated: 2025/02/04 13:31:15 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_message(char *msg, t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->start_time;
	pthread_mutex_lock(&philo->lock);
	// if (!dead_philo(philo))
	printf("%zu %d %s\n", time, philo->threads->id, msg);
	pthread_mutex_unlock(&philo->lock);
	return (TRUE);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms, t_philo *philo)
{
	size_t	i;
	size_t	start;
	
	i = 0;
	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (i % 200 == 0)
		{
			pthread_mutex_lock(&philo->lock);
			if (philo->dead)
				return (pthread_mutex_unlock(&philo->lock));
			pthread_mutex_unlock(&philo->lock);
		}
		usleep(500);
		i++;
	}
	return (TRUE);
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
			return (FALSE);
		str++;
	}
	return (TRUE);
}

size_t	ft_atoi(char *str)
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
