/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:52:00 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/14 10:53:11 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* free_table:
*	Frees all of the memory allocated by the program.
*	Returns a NULL pointer if there is nothing to free,
*	or when all memory has been freed.
*/
void	free_table(t_table *table)
{
	if (!table)
		return ;
	destroy_mutexes(table);
	if (table->fork_locks)
		free(table->fork_locks);
	if (table->philos)
		free(table->philos);
	free(table);
}

/* destroy_mutexts:
*	Destroys every mutex created by the program: fork locks, meal locks,
*	the write and simulation stopper lock.
*/
void	destroy_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	if (table->fork_locks)
	{
		while (i < table->nb_philos)
		{
			pthread_mutex_destroy(&table->fork_locks[i]);
			i++;
		}
	}
	i = 0;
	if (table->philos)
	{
		while (i < table->nb_philos)
		{
			pthread_mutex_destroy(&table->philos[i].meal_time_lock);
			i++;
		}
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}

int	error_failure(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	if (details)
		printf("Error: %s: %s\n", str, details);
	else
		printf("Error: %s\n", str);
	return (EXIT_FAILURE);
}

/* error_null:
*	Frees any allocated memory, prints error message & returns a NULL pointer
*	Used for error management during initialization.
*/
void	*error_null(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	if (details)
		printf("Error: %s: %s\n", str, details);
	else
		printf("Error: %s\n", str);
	return (NULL);
}
