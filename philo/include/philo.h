/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:32 by prynty            #+#    #+#             */
/*   Updated: 2025/02/11 14:28:01 by prynty           ###   ########.fr       */
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

typedef struct s_thread
{
	pthread_t		thread;
	size_t			id;
	size_t			philos_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_times_to_eat;
	size_t			meals_eaten;
	size_t			start_time;
	size_t			*full_philos;
	size_t			prev_meal;
	int				*dead_or_full;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*data_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_table
{
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	data_lock;
	int				dead_or_full;
	size_t			full_philos;
}	t_table;

//errors.c
void	print_usage(void);
void	print_error(char *msg);
t_table	*terminate(t_table *table, char *str, size_t i);

//forks.c
int		lock_forks_even(t_philo *philo);
int		lock_forks_odd(t_philo *philo);
void	unlock_forks_even(t_philo *philo);
void	unlock_forks_odd(t_philo *philo);

//init.c
t_table	*init_data(char **argv);

//routine.c
void	*routine(void *ptr);
void	*monitoring(void *ptr);

//threads.c
int		time_to_stop(t_philo *philo);
int		dead_or_full(t_table *table);
int		join_thread(t_table *table);
int		create_thread(t_table *table);

//utils.c
int		print_message(char *msg, t_philo *philo);
size_t	get_time(void);
int		ft_usleep(t_philo *philo, size_t ms);
size_t	ft_atol(char *str);

#endif