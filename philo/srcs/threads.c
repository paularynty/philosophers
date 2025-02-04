/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:40 by prynty            #+#    #+#             */
/*   Updated: 2025/01/31 14:33:23 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_thread(t_philo *philo)
{
	size_t	i;

	i = 0;
	printf("%zu\n", philo->num_of_philos - 1);
	while (i < philo->num_of_philos - 1)
	{
		if (pthread_create(&(philo->threads[i].thread), NULL, &routine,
				&philo->threads[i]) != 0)
			return (terminate("Error creating threads", philo), 1);
		i++;
	}
	return (0);
}
