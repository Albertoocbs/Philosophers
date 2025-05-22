/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:51:54 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/22 13:55:55 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOS 200

// ----------- Error messages -----------

# define ERR_ARGC "Error: wrong number of arguments\n"
# define ERR_NOT_DIGIT "Error: argument %d is not a digit\n"
# define ERR_INVALID_INT "Error: argument value must be positive.\n"
# define ERR_PHILO_MAX "Error: num of philosophers must be between 1 & %d\n"

/*--------------Structures-----------------*/

typedef struct s_table	t_table;
typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	time_t				last_meal;
	pthread_mutex_t		meal_time_lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	time_t				start_time;
	unsigned int		nb_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					must_eat_count;
	bool				sim_stop;
	pthread_mutex_t		sim_stop_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		fork_locks[MAX_PHILOS];
	t_philo				philos[MAX_PHILOS];
}						t_table;

/*----------------Prototypes---------------*/
/*--------------Initialization-------------*/
bool					init_table(t_table *table, int argc, char **argv);
bool					init_philosophers(t_table *table);
bool					init_mutexes(t_table *table);
void					assign_forks(t_table *table);
void					assign_fork_order(t_philo *philo);

/*----------------Parsing----------------*/
int						is_only_digits(char *str);
int						ft_atoi(char *str);
int						is_valid_input(int argc, char **argv);

/*----------------Utils---------------------*/
void					destroy_mutexes(t_table *table);
long					get_time(void);
void					ft_usleep(unsigned int time_in_ms, t_table *table);
void					safe_print(t_table *table, int id, char *msg);

/*--------------Philosophers-------------*/
void					*philo_routine(void *arg);
void					eat(t_philo *philo);
void					sleep_and_think(t_philo *philo);
void					take_forks(t_philo *philo);
void					drop_forks(t_philo *philo);

/*--------------Monitor--------------*/
bool					monitor(t_table *table);
bool					get_sim_stop(t_table *table);
void					set_sim_stop(t_table *table);
bool					check_all_ate(t_table *table);

#endif
