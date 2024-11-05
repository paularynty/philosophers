/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:06:30 by prynty            #+#    #+#             */
/*   Updated: 2024/11/05 19:04:19 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		print_error("Usage: ./philo number_of_philosophers time_to_die time_to_eat\
			time_to_sleep number_of_times_each_philosopher_must_eat");
	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			print_error("Arguments must be a positive number");
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philos)
{
	int	i;

	i = 0;
	while (i < philos)
		if (pthread_mutex_init(&forks[i++], NULL) == -1)
			print_error("Fork error");
}

void	init_struct(t_philo *philos, int argc, char **argv)
{
	philos->argc = argc;
	philos->argv = argv;
	philos->num_of_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philos->num_times_to_eat = ft_atoi(argv[5]);
	else
		philos->num_times_to_eat = -1;
	philos->start_time = get_current_time();
	if (philos->num_of_philos > PHILO_MAX)
		print_error("Too many philosophers");
}
