/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:20 by prynty            #+#    #+#             */
/*   Updated: 2024/10/19 15:47:29 by prynty           ###   ########.fr       */
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

static size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday failed\n", 21);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static int	is_digit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static size_t	ft_atoi(char *str)
{
	long	result;
	long	check;

	result = 0;
	check = result;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return ((size_t)(result));
}

void	print_error(char *msg)
{
	printf(RED"Error\n"RESET);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		print_error("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat");
	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			print_error("Arguments must be a positive number");
		i++;
	}
}

void	init_struct(t_philo *philos, int argc, char **argv)
{
	philos->argc = argc;
	philos->argv = argv;
	philos->num_of_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (philos->argc == 6)
		philos->num_times_to_eat = ft_atoi(argv[5]);
	else
		philos->num_times_to_eat = -1;
	philos->start_time = get_current_time();
	if (philos->num_of_philos > PHILO_MAX)
		print_error("Too many philosophers");
}

static int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

pthread_mutex_t	mutex;

void	routine(void) 
{
	int	i;
	
	i = 0;
	while (i < 5)
	{
		i++;
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d has taken a fork\n", i);
		ft_usleep(500);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d is eating\n", i);
		ft_usleep(500);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d is thinking\n", i);
		ft_usleep(500);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d is sleeping\n", i);
		ft_usleep(500);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex);
		printf("Philosopher %d died\n", i);
		ft_usleep(500);
		pthread_mutex_unlock(&mutex);
	}
}

int	main(int argc, char **argv) 
{
	pthread_t		t1;
	pthread_t		t2;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	// t_program	program;

	// memset(&philo, 0, sizeof(t_philo));
	validate_args(argc, argv);
	init_struct(philos, argc, argv);
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
