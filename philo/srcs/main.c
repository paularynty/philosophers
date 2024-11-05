/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:20 by prynty            #+#    #+#             */
/*   Updated: 2024/11/05 18:57:12 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	dead_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

//dead_lock to give time for the program to check for dead philos
int	dead_check(t_program *program)
{
	pthread_mutex_lock(&program->dead_lock);
	if (program->dead_flag)
		return (pthread_mutex_unlock(&program->dead_lock), 1);
	pthread_mutex_unlock(&program->dead_lock);
	return (0);
}

void	print_message(char *msg, t_philo *philo, int id)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!dead_philo(philo))
		printf("%zu %d %s\n", time, id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

// void	lonely_philo(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->r_fork);
// 	print_message(RFORK, philo, philo->id);
// 	pthread_mutex_lock(philo->r_fork);
// 	print_message(EAT, philo, philo->id);
// }

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(RFORK, philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message(LFORK, philo, philo->id);
	philo->eating = 1;
	print_message(EAT, philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping(t_philo *philo)
{
	print_message(SLEEP, philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	*routine(void *ptr) 
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	// if (philo->num_of_philos == 1)
	// 	lonely_philo(philo);
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_philo(philo))
	{
		eating(philo);
		sleeping(philo);
		print_message(THINK, philo, philo->id); //from separate think func
	}
	return (ptr);
}

void	*monitor(void *ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)ptr;
	while (1)
		if (dead_check(philo) || all_eaten(philo))
			break ;
	return (ptr);
}

static int	create_thread(t_philo *philo, pthread_mutex_t *forks)
{
	size_t			i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		if (pthread_create(&(philo->)))
	}
	// pthread_t		observer;
	
	// if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
	// 	destroy_all("Error creating thread", program, forks);
	// i = 0;
	// while (i < program->philos[0].num_of_philos)
	// {
	// 	if (pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]) != 0)
	// 		destroy_all("Error creating thread", program, forks);
	// 	i++;
			
	// }
	// i = 0;
	// if (pthread_join(observer, NULL) != 0)
	// 	destroy_all("Error joining thread", program, forks);
    // while (i < program->philos[0].num_of_philos)
	// {
	// 	if (pthread_join(program->philos[i].thread, NULL) != 0)
	// 		destroy_all("Error joining thread", program, forks);
	// 	i++;
	// }
	// return (0);
}

int	main(int argc, char **argv) 
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	validate_args(argc, argv);
	init_struct(philos, argc, argv);
	init_forks(forks, philos->num_of_philos);
	create_thread(&program, forks);
	terminate(NULL, &program, forks);
	return (0);
}