/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:46:25 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/20 13:45:42 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

/*
 *	Uses gettimeofday to get the current time and convert it to milliseconds.
 *	- tv.tv_sec * 1000 ➔ conversion of seconds in miliseconds
 *	- tv.tv_usec / 1000 ➔ conversion of microseconds in miliseconds
 *	Returns the time in milliseconds
 */
long	get_time(void)
{
	struct timeval	tv;
	long long		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

/*
 *	If get_sim_stop is triggered (true) during the sleep period,
 *	the thread can react immediately and exit early, preventing delays.
 *	Otherwise, the thread sleeps for the specified time until time is up.
 */
void	ft_usleep(unsigned int time_in_ms, t_table *table)
{
	time_t	start;

	start = get_time();
	while (1)
	{
		if (get_sim_stop(table) == true)
			break ;
		if ((get_time() - start) >= time_in_ms)
			break ;
		usleep(500);
	}
}

/*
	Prints a threadsafe message with timestamp, philosopher ID, and the message.
	Example: "123 2 is eating"
*/
void	safe_print(t_table *table, int id, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&table->write_lock);
	if (!get_sim_stop(table))
	{
		timestamp = get_time() - table->start_time;
		printf("%lld %d %s\n", timestamp, id + 1, msg);
	}
	pthread_mutex_unlock(&table->write_lock);
}
