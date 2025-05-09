/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:05:33 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/05 14:24:28 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
void	ft_usleep(useconds_t time_in_ms, t_table *table)
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
