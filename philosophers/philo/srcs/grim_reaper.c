/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:39:24 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/05 14:23:57 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Monitors the philosophers last meal times to check if any philosopher
	has died. If a philosopher has not eaten for too long, the simulation
	is stopped.
*/
void	*monitor(void *arg)
{
	t_table			*table;
	unsigned int	i;

	table = (t_table *)arg;
	while (!get_sim_stop(table))
	{
		i = 0;
		while (i < table->nb_philos)
		{
			pthread_mutex_lock(&table->philos[i].meal_time_lock);
			if (get_time() - table->philos[i].last_meal > table->time_to_die)
			{
				safe_print(table, table->philos[i].id, "died");
				set_sim_stop(table);
				pthread_mutex_unlock(&table->philos[i].meal_time_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philos[i].meal_time_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

/*
	Reads the value of the sim_stop variable in a thread-safe manner.
	This function is used to check if the simulation should stop.
*/
bool	get_sim_stop(t_table *table)
{
	bool	value;

	pthread_mutex_lock(&table->sim_stop_lock);
	value = table->sim_stop;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (value);
}

/*
	Sets/modifies the sim_stop value to true in a thread-safe manner.
	This function is used to stop the simulation when a philosopher dies.
*/
void	set_sim_stop(t_table *table)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
}
