/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:15:54 by prynty            #+#    #+#             */
/*   Updated: 2025/02/10 20:13:02 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (FALSE);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!validate_args(argc, argv))
	{
		print_usage();
		return (1);
	}
	table = init_data(argv);
	if (table == NULL)
	{
		print_error("Failed to initialize program");
		return (1);
	}
	if (!create_thread(table))
		return (1);
	monitoring(table);
	if (!join_thread(table))
		return (1);
	terminate(table, NULL, 0);
	return (0);
}
