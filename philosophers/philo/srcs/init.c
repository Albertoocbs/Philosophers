/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:52:03 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/08 11:03:32 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(int argc, char **argv, int i)
{
	t_table	*table;

	(void)argc;
	(void)i;
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
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
	table->fork_locks = NULL;
	table->philos = NULL;
	return (table);
}

bool	init_mutexes(t_table *table)
{
	unsigned int	i;

	if (pthread_mutex_init(&table->sim_stop_lock, NULL) != 0
		|| pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (false);
	table->fork_locks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->fork_locks)
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

t_philo	*init_philosophers(t_table *table)
{
	t_philo			*philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!philos)
		return (error_null("malloc failed (philos)", NULL, table));
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&philos[i].meal_time_lock, NULL) != 0)
			return (error_null("mutex init failed (meal_time)", NULL, table));
		philos[i].id = i;
		philos[i].table = table;
		philos[i].times_ate = 0;
		philos[i].last_meal = get_time();
		i++;
	}
	assign_forks(table, philos);
	return (philos);
}

void	assign_forks(t_table *table, t_philo *philos)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		philos[i].left_fork = &table->fork_locks[i];
		philos[i].right_fork = &table->fork_locks[(i + 1) % table->nb_philos];
		assign_fork_order(&philos[i]);
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
