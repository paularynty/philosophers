/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:32 by prynty            #+#    #+#             */
/*   Updated: 2024/11/05 18:51:48 by prynty           ###   ########.fr       */
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

# define RFORK "has taken a fork"
# define LFORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DIED "died"

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

//errors.c
void	print_error(char *msg);
void	terminate(char *str, t_program *program, pthread_mutex_t *forks);

//init.c
void	validate_args(int argc, char **argv);
void	init_struct(t_philo *philos, int argc, char **argv);
void	init_forks(pthread_mutex_t *forks, int philos);

//utils.c
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
int		is_digit(char *str);
size_t	ft_atoi(char *str);

#endif