/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:32 by prynty            #+#    #+#             */
/*   Updated: 2025/02/18 10:33:20 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0

# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DIED "died"

# define RED "\033[1;91m"
# define PINK "\e[1m\e[38;5;206m"
# define RESET "\033[0;39m"

typedef struct s_table	t_table;

typedef struct s_philo
{
	t_table			*table;
	size_t			id;
	size_t			prev_meal;
	size_t			meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	data_lock;
	size_t			philos_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_times_to_eat;
	size_t			start_time;
	size_t			full_philos;
	_Atomic int		sim_start;
	_Atomic int		dead_or_full;
}	t_table;

//cleanup.c
int		usage(void);
void	print_error(char *msg);
int		terminate_init(char *str, t_table *table, int destroy_prev_lock);
int		cleanup(char *str, t_table *table);

//forks.c
void	unlock_forks(t_philo *philo);
int		lock_forks_even(t_philo *philo);
int		lock_forks_odd(t_philo *philo);

//init.c
int		validate_args(int argc, char **argv);
int		init_data(t_table *table, char **argv);

//routine.c
void	*routine(void *ptr);
void	*monitoring(void *ptr);

//threads.c
int		time_to_stop(t_philo *philo);
int		dead_or_full(t_table *table);
int		join_thread(t_table *table);
void	*sync_threads(void *ptr);
int		create_thread(t_table *table);

//utils.c
int		print_message(char *msg, t_philo *philo);
size_t	get_time(void);
int		ft_usleep(size_t ms, t_table *table);
int		is_digit(char *str);
size_t	ft_atol(char *str);

#endif