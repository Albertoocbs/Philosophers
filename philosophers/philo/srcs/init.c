/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:52:03 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/20 13:44:02 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_table(t_table *table, int argc, char **argv)
{
	table->nb_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = -1;
	table->sim_stop = false;
	table->start_time = get_time();
	return (true);
}

bool	init_mutexes(t_table *table)
{
	unsigned int	i;

	if (pthread_mutex_init(&table->sim_stop_lock, NULL) != 0
		|| pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (false);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->fork_locks[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

bool	init_philosophers(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->philos[i].meal_time_lock, NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&table->philos[i].meal_time_lock);
			}
			printf("Error: mutex init failed (meal time)\n");
			return (false);
		}
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].times_ate = 0;
		table->philos[i].last_meal = get_time();
		i++;
	}
	assign_forks(table);
	return (true);
}

void	assign_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].left_fork = &table->fork_locks[i];
		table->philos[i].right_fork = &table->fork_locks[(i + 1)
			% table->nb_philos];
		assign_fork_order(&table->philos[i]);
		i++;
	}
}

void	assign_fork_order(t_philo *philo)
{
	pthread_mutex_t	*tmp;

	if (philo->id % 2)
	{
		tmp = philo->left_fork;
		philo->left_fork = philo->right_fork;
		philo->right_fork = tmp;
	}
}
