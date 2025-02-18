/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:15:54 by prynty            #+#    #+#             */
/*   Updated: 2025/02/18 10:31:37 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (usage());
	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (usage());
		i++;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!validate_args(argc, argv))
		return (1);
	if (!init_data(&table, argv))
		return (1);
	if (!create_thread(&table))
		return (1);
	monitoring(&table);
	if (!join_thread(&table))
		return (1);
	cleanup(NULL, &table);
	return (0);
}
