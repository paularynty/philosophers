/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:32 by prynty            #+#    #+#             */
/*   Updated: 2024/11/06 19:31:07 by prynty           ###   ########.fr       */
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

# define SUCCESS 1
# define FAILURE 0

# define RFORK "has taken a fork"
# define LFORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DIED "died"

# define RED "\033[1;91m"
# define RESET "\033[0;39m"

typedef struct s_philo	t_philo;

typedef struct s_thread
{
	t_philo			*philo;
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_thread;

typedef struct s_philo
{
	t_thread		*threads;
	size_t			num_of_philos;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*forks;
}	t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

//errors.c
void	print_error(char *msg);
void	terminate(char *str, t_philo *philo);

//init.c
void	validate_args(int argc, char **argv);
void	init_struct(t_philo *philos, char **argv);
void	init_forks(t_philo *philo);

//routine.c
int		eating(t_philo *philo);
int		thinking(t_philo *philo);
int		sleeping(t_philo *philo);
void	*routine(void *ptr);

//threads.c
int		create_thread(t_philo *philo);

//utils.c
int		print_message(char *msg, t_philo *philo);
size_t	get_time(void);
int		ft_usleep(size_t ms);
int		is_digit(char *str);
size_t	ft_atoi(char *str);

#endif