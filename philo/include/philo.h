/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:32 by prynty            #+#    #+#             */
/*   Updated: 2025/02/10 15:25:10 by prynty           ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef struct s_thread
{
	t_philo			*philo;
	size_t			id;
	size_t			prev_meal;
	size_t			meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_thread;

typedef struct s_philo
{
	t_thread		*threads;
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
	int				dead_or_full;
}	t_philo;

//errors.c
void	usage(void);
void	print_error(char *msg);
void	terminate(char *str, t_philo *philo);

//forks.c
int		lock_forks_even(t_thread *thread);
int		lock_forks_odd(t_thread *thread);
void	unlock_forks_even(t_thread *thread);
void	unlock_forks_odd(t_thread *thread);

//init.c
int		validate_args(int argc, char **argv);
int		init_data(t_philo *philo, char **argv);

//routine.c
int		print_message(char *msg, t_thread *thread);
void	*routine(void *ptr);

//threads.c
int		time_to_stop(t_thread *thread);
int		dead_or_full(t_philo *philo);
void	*monitoring(void *ptr);
int		join_thread(t_philo *philo);
int		create_thread(t_philo *philo);

//utils.c
size_t	get_time(void);
int		ft_usleep(size_t ms, t_philo *philo);
int		is_digit(char *str);
size_t	ft_atol(char *str);

#endif