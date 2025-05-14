/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:58:02 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/14 12:13:57 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_routine, &table->philos[i]) != 0)
		{
			printf("Error: Failed to create thread for philo %d\n", i + 1);
			return (false);
		}
		i++;
	}
	return (true);
}

void	join_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

/* start_simulation function*/
bool	start_simulation(t_table *table)
{
	if (!create_threads(table))
		return (false);
	if (!monitor(table))
		return (false);
	join_threads(table);
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc != 5 && argc != 6)
		return (printf(ERR_ARGC), 0);
	if (!is_valid_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!init_mutexes(table))
		return (free_table(table), 1);
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (free_table(table), 1);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	free_table(table);
	return (EXIT_SUCCESS);
}
