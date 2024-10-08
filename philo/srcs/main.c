/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <paula.rynty@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:20 by prynty            #+#    #+#             */
/*   Updated: 2024/10/08 15:41:31 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
1. Create a data structure to store all required information about a philosopher
2. Create the correct number of philosopher
3. Create the correct number of threads
4. Create a routine (what each philosopher has to do? in which order?)
5. Initiate the threads with said routine
*/

#include "../include/philo.h"

//number of philosophers, time to die, time to eat, time to sleep, (number 
//of times each philosopher must eat)
int	main(int argc, char **argv)
{
	t_philo	philo;
	size_t	i;
	pthread_mutex_t	mutex;

	i = 0;
	(void)argv;
	if (argc != 6)
	{
		write(2, "Usage: ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat\n", 125);
		return (-1);
	}
	pthread_mutex_init(&mutex, NULL);
	while (i <= philo.nbr)
	{
		pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
