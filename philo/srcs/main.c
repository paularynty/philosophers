/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:15:54 by prynty            #+#    #+#             */
/*   Updated: 2024/11/06 19:38:51 by prynty           ###   ########.fr       */
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

int main(int argc, char **argv)
{
    t_philo philo;
    validate_args(argc, argv);
    init_struct(&philo, argv);
	create_thread(&philo);
    return (0);   
}