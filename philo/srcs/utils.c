/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:18:52 by prynty            #+#    #+#             */
/*   Updated: 2025/02/08 19:51:28 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(char *msg, t_thread *thread)
{
	size_t	time;

	time = get_time() - thread->philo->start_time;
	pthread_mutex_lock(&thread->philo->print_lock);
	//add death lock
	if (thread->philo->dead_or_full)
	{
		pthread_mutex_unlock(&thread->philo->print_lock);
		return (FALSE);
	}
	printf("%zu %zu %s\n", time, thread->id, msg);
	pthread_mutex_unlock(&thread->philo->print_lock);
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
			pthread_mutex_lock(&philo->data_lock);
			if (philo->dead_or_full)
				return (pthread_mutex_unlock(&philo->data_lock), FALSE);
			pthread_mutex_unlock(&philo->data_lock);
		}
		usleep(100);
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
