/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:38:32 by prynty            #+#    #+#             */
/*   Updated: 2024/10/12 15:42:31 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h> //for malloc, free
# include <stdio.h> //for printf
# include <pthread.h> //for pthread functions
# include <sys/time.h> //for gettimeofday
# include <unistd.h> //for write, usleep
# include <semaphore.h> //for sem_functions

# define PHILOS 200

typedef struct s_philo
{
	int			argc;
	char		**argv;
	pthread_t	thread;
	int			die;
	int			eat;
	int			sleep;
	int			id; //individual philo id
	size_t		nbr; //nbr of philosophers
}	t_philo;

#endif