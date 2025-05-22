/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:58:13 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/22 13:31:47 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nb_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo->table, philo->id, "has taken a fork");
		while (!get_sim_stop(philo->table))
			usleep(1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!get_sim_stop(philo->table))
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	safe_print(philo->table, philo->id, "is eating");
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time();
	philo->times_ate++;
	pthread_mutex_unlock(&philo->meal_time_lock);
	ft_usleep(philo->table->time_to_eat, philo->table);
}

void	sleep_and_think(t_philo *philo)
{
	safe_print(philo->table, philo->id, "is sleeping");
	ft_usleep(philo->table->time_to_sleep, philo->table);
	safe_print(philo->table, philo->id, "is thinking");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	safe_print(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	safe_print(philo->table, philo->id, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
