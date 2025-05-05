/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:06:21 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/05 14:24:11 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
