/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:32 by prynty            #+#    #+#             */
/*   Updated: 2024/10/19 15:43:53 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h> //for malloc, free
# include <stdio.h> //for printf
# include <string.h> //for memset
# include <pthread.h> //for pthread functions
# include <sys/time.h> //for gettimeofday
# include <unistd.h> //for write, usleep

# define PHILO_MAX 200
# define RED "\033[1;91m"
# define RESET "\033[0;39m"

typedef struct s_philo
{
	int				argc;
	char			**argv;
	pthread_t		thread;
	int				id; //individual philo id
	int				num_of_philos;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

#endif