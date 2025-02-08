/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:15:54 by prynty            #+#    #+#             */
/*   Updated: 2025/02/08 17:23:07 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (!validate_args(argc, argv))
		return (1);
	if (!init_data(&philo, argv))
		return (1);
	if (!create_thread(&philo))
		return (1);
	// simulation(&philo);
	stop_thread(&philo);
	if (!join_thread(&philo))
		return (1);
	terminate(NULL, &philo);
	return (0);
}
