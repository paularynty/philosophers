/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:20 by prynty            #+#    #+#             */
/*   Updated: 2024/10/12 16:47:59 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
TODO:
1. Create a data structure to store all required information about a philosopher
2. Create the correct number of philosopher
3. Create the correct number of threads
4. Create a routine (what each philosopher has to do? in which order?)
5. Initiate the threads with said routine
*/

// void	init_struct(t_philo *philo)
// {
// 	philo->argc = argc;
// 	philo->argv = argv;
// 	philo->nbr = argv[1];
// 	philo->die = argv[2];
// 	philo->eat = argv[3];
// 	philo->sleep = argv[4];
// }

// static int	validate_args(t_philo *philo)
// {
// 	if (philo->argc != 6)
// 	{
// 		write(2, "Usage: ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat\n", 125);
// 		return (1);
// 	}
// 	return (0);
// }

// //number of philosophers, time to die, time to eat, time to sleep, (number 
// //of times each philosopher must eat)
// int	main(int argc, char **argv)
// {
// 	t_philo	philo;
// 	size_t	i;
// 	pthread_mutex_t	mutex;

// 	i = 0;
// 	init_struct(&philo);
// 	if (validate_args(&philo))
// 		return (-1);
// 	pthread_mutex_init(&mutex, NULL);
// 	while (i <= philo.nbr)
// 	{
// 		pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	return (0);
// }

pthread_mutex_t	mutex;


void	routine(void) 
{
	int i = 0;
	while (i < 5)
	{
		i++;
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d has taken a fork\n", i);
		usleep(5000);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d is eating\n", i);
		usleep(5000);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d is thinking\n", i);
		usleep(5000);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d is sleeping\n", i);
		usleep(5000);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d died\n", i);
		usleep(5000);
		pthread_mutex_unlock(&mutex);
	}
}

int	main(void) 
{
	pthread_t	t1;
	pthread_t	t2;
	
	pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&t1, NULL, (void *)routine, NULL) != 0)
	{
		printf("Error creating thread 1");
		return (1);
	}
    if (pthread_create(&t2, NULL, (void *)routine, NULL) != 0)
    {
		printf("Error creating thread 2");
		return (1);
	}
    if (pthread_join(t1, NULL) != 0)
    {
		printf("Error joining thread 1");
		return (1);
	}
    if (pthread_join(t2, NULL) != 0)
    {
		printf("Error joining thread 2");
		return (1);
	}
	pthread_mutex_destroy(&mutex);
	printf("Done\n");
    return (0);
}
