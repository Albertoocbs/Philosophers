/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:39:24 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/08 11:48:58 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
*	Checks if all philosophers have eaten the required number of times
*	Returns true if all philosophers have eaten the required number of times
*/
bool	check_all_ate(t_table *table)
{
	unsigned int	i;
	unsigned int	finished;

	finished = 0;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_time_lock);
		if (table->philos[i].times_ate >= (unsigned int)table->must_eat_count)
			finished++;
		pthread_mutex_unlock(&table->philos[i].meal_time_lock);
		i++;
	}
	if (finished == table->nb_philos)
	{
		safe_print(table, 0, "all philos have eaten the specified x times");
		return (true);
	}
	return (false);
}

/*
*	Checks if a philosopher has died
*	Returns true if a philosopher has died and false otherwise
*	Locks the meal_time_lock mutex of each philosopher to check last meal time
*	Compares the last meal time with the current time and the time to die
*/
bool	check_philo_death(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_time_lock);
		if (get_time() - table->philos[i].last_meal > table->time_to_die)
		{
			safe_print(table, table->philos[i].id, "died");
			set_sim_stop(table);
			pthread_mutex_unlock(&table->philos[i].meal_time_lock);
			return (true);
		}
		pthread_mutex_unlock(&table->philos[i].meal_time_lock);
		i++;
	}
	return (false);
}

/*
	Monitor thread function that checks if a philosopher has died or
	if all philosophers have eaten the required number of times.
	It runs in a loop until the simulation is stopped.
	Returns NULL when the simulation is stopped or when a philosopher dies.
	Uses usleep to avoid busy waiting.
*/
void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!get_sim_stop(table))
	{
		if (check_philo_death(table))
			return (NULL);
		if (table->must_eat_count != -1 && check_all_ate(table))
		{
			set_sim_stop(table);
			return (NULL);
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
