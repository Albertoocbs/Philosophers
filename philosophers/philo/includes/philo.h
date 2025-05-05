/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:51:54 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/05 14:27:59 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

# define MAX_PHILOS 200

// ----------- Error messages -----------

# define ERR_ARGC			"Error: wrong number of arguments\n"
# define ERR_NOT_DIGIT		"Error: argument %d is not a digit\n"
# define ERR_INVALID_INT	"Error: argument value must be positive.\n"
# define ERR_PHILO_MAX	"Error: num of philosophers must be between 1 & %d\n"

/*--------------Structures-----------------*/

typedef struct s_table	t_table;
typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	time_t			last_meal;
	pthread_mutex_t	meal_time_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		grim_reaper;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			*philos;
}	t_table;

/*----------------Prototypes---------------*/
/*--------------Error_Handling-------------*/
void	free_table(t_table *table);
void	destroy_mutexes(t_table *table);
void	*error_null(char *str, char *details, t_table *table);
int		error_failure(char *str, char *details, t_table *table);

/*--------------Initialization-------------*/
t_table	*init_table(int argc, char **argv, int i);
t_philo	*init_philosophers(t_table *table);
bool	init_mutexes(t_table *table);
void	assign_forks(t_table *table, t_philo *philos);
void	assign_fork_order(t_philo *philo);

/*----------------Parsing----------------*/
int		is_only_digits(char *str);
int		ft_atoi(char *str);
int		is_valid_input(int argc, char **argv);

/*----------------get_time-------------------*/
long	get_time(void);

/*----------------ft_usleep----------------*/
void	ft_usleep(useconds_t time_in_ms, t_table *table);

/*--------------Philosophers-------------*/
void	*philo_routine(void *arg);
void	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);

/*--------------Grim_Reaper--------------*/
void	*monitor(void *arg);
bool	get_sim_stop(t_table *table);
void	set_sim_stop(t_table *table);

/*--------------Output------------------*/
void	safe_print(t_table *table, int id, char *msg);

#endif
