/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:20 by prynty            #+#    #+#             */
/*   Updated: 2024/11/05 13:18:50 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!dead(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	thinking(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	sleeping(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead = 1);
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *ptr) 
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while(!dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (ptr);
}
// void	routine(void) 
// {
// 	int	i;
	
// 	i = 0;
// 	while (i < 5)
// 	{
// 		i++;
// 		pthread_mutex_lock(&mutex);
// 		printf("Philosopher %d has taken a fork\n", i);
// 		ft_usleep(500);
// 		pthread_mutex_unlock(&mutex);
// 		pthread_mutex_lock(&mutex);
// 		printf("Philosopher %d is eating\n", i);
// 		ft_usleep(500);
// 		pthread_mutex_unlock(&mutex);
// 		pthread_mutex_lock(&mutex);
// 		printf("Philosopher %d is thinking\n", i);
// 		ft_usleep(500);
// 		pthread_mutex_unlock(&mutex);
// 		pthread_mutex_lock(&mutex);
// 		printf("Philosopher %d is sleeping\n", i);
// 		ft_usleep(500);
// 		pthread_mutex_unlock(&mutex);
// 		pthread_mutex_lock(&mutex);
// 		printf("Philosopher %d died\n", i);
// 		ft_usleep(500);
// 		pthread_mutex_unlock(&mutex);
// 	}
// }

static int	create_thread(void)
{
	pthread_t		t1;
	pthread_t		t2;
	
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
	return (0);
}

int	main(int argc, char **argv) 
{
	t_program	program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	// memset(&philo, 0, sizeof(t_philo));
	validate_args(argc, argv);
	init_struct(philos, argc, argv);
	init_forks(forks, philos->num_of_philos);
	create_thread();
	destroy_all(&program, forks);
	printf("Done\n");
	return (0);
}
