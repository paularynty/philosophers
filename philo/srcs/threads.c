/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:40 by prynty            #+#    #+#             */
/*   Updated: 2024/11/06 18:56:00 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_thread(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		if (pthread_create(&(philo->threads[i].thread), NULL, &routine,
				&philo->threads[i]) != 0)
			print_error("Error creating threads");
		i++;
	}
	return (0);
}
