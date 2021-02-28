/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:59:17 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/28 22:12:56 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "stdio.h"
# include "string.h"
# include "unistd.h"
# include "sys/time.h"
# include "pthread.h"
# include "stdlib.h"

#define STDERR 2

# define ARG_NUM_ERROR "Number of arguments isn't valid!"
# define ARG_FORMAT_ERROR "Fpormat or value of arguments isn't valid!"
# define PHILOS_INIT_ERROR "Error during philosophers initialisation!"
# define PHILOS_SIMULATE_ERROR "Error during philosophers simulation!"
# define PHILOS_CLOSE_ERROR "Error during philosophers closing!"

# define OK 1
# define KO -1

# define FIRST 0
# define SECOND 1

# define TAKE_RIGHT "has taken a right fork"
# define TAKE_LEFT "has taken a left fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "is deied"

typedef pthread_mutex_t	t_mutex;

typedef struct	s_args
{
	size_t		num_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	long		need_num_eat;
}				t_args;

typedef struct	s_philo
{
	long		i;
	size_t		*num_philos_have_eaten;
	int			*thereis_died;
	int			*status;
	size_t		*begin_time;
	size_t		time_last_eat;
	long		num_eat;
	t_mutex		eat_m;
	t_mutex		*leftfork_m;
	t_mutex		*rightfork_m;
	t_mutex		*printer_m;
	t_args		*args;
	pthread_t	thread;
}				t_philo;

typedef struct	s_game
{
	int			status;
	size_t		num_philos_have_eaten;
	int			thereis_died;
	size_t		begin_time;
	t_args		args;
	t_mutex		*forks_m;
	t_mutex		*printer_m;
	t_philo		*philos;
}				t_game;

/*
**init_game.c - functions for initialisation of philosophers
*/

int				init_args(int argc, char **argv, t_args *args);
int				check_args(int argc, char **argv);
int				init_one_mutex(t_mutex **mutex);
int				init_forks(size_t num_forks, t_mutex **forks);
int				init_philos(t_game *game, t_philo **philos);

/*
**thread.c - functions for creation detaching and joining threads
*/

int				join_philo_threads(t_philo *philos, size_t num);
int				create_philo_threads(t_philo *philos, size_t num,
									size_t begin_i);
int				init_thread_detach(pthread_t *thread,
									void *(*rtn) (void *), void *args);
/*
**routine.c - functions wich exucuting in threads
*/

void			*routine(void *args);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			*monitor_death(void *args);
void			*monitor_num_eat(void *args);

/*
**close_game.c - functions closing philosphers
*/

void			close_forks(size_t num_forks, t_mutex *forks);
void			close_one_mutex(t_mutex *mutex);

/*
**print.c - functions info printing in STDOUT
*/

void			print_error(char *error);
int				print_action_wrap(t_philo *philo, char *action);
void			print_action(size_t time, long num, char *action,
							t_mutex *printer);
/*
**time.c - functions for time treating
*/

size_t			get_difftime(size_t time);
size_t			get_currtime(void);
void			sleep_for(size_t time);

/*
**utils.c
*/

void			ft_bzero(void *mem, size_t n);
unsigned int	ft_atoui(const char *str);
int				ft_isdigit(int ch);
int				ft_isspace(int ch);

#endif
