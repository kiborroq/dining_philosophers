/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:59:17 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/03 21:34:23 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include "stdio.h"
# include "string.h"
# include "unistd.h"
# include "sys/time.h"
# include "sys/stat.h"
# include "sys/types.h"
# include "pthread.h"
# include "stdlib.h"
# include "semaphore.h"
# include "fcntl.h"
# include "sys/wait.h"
# include "signal.h"

# define STDERR 2

# define ARG_NUM_ERROR "Number of arguments isn't valid!"
# define ARG_FORMAT_ERROR "Fpormat or value of arguments isn't valid!"
# define PHILOS_INIT_ERROR "Error during philosophers initialisation!"
# define PHILOS_SIMULATE_ERROR "Error during philosophers simulation!"
# define PHILOS_CLOSE_ERROR "Error during philosophers closing!"

# define FORKS_S "/forks_s"
# define PRINTER_S "/printe_s"
# define PREFIX_EAT_S_ "/eat_s_"

# define WAIT_NEXT 5
# define KILL_ALL 10

# define VALBINARY_S 1

# define OK 1
# define KO -1

# define FIRST 0
# define SECOND 1

# define TAKE "has taken fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "is deied"

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
	char		*sem_eat_name;
	size_t		*num_philos_have_eaten;
	int			*status;
	size_t		*begin_time;
	size_t		time_last_eat;
	long		num_eat;
	sem_t		*eat_s;
	sem_t		*forks_s;
	sem_t		*printer_s;
	t_args		*args;
}				t_philo;

typedef struct	s_game
{
	int			status;
	size_t		num_philos_have_eaten;
	int			thereis_died;
	size_t		begin_time;
	t_args		args;
	char		**names;
	sem_t		**eats_s;
	sem_t		*forks_s;
	sem_t		*printer_s;
	pid_t		*pids;
	t_philo		*philos;
}				t_game;

/*
**init_game.c - functions for initialisation of philosophers
*/

int				init_args(int argc, char **argv, t_args *args);
int				init_one_sem(char *name, size_t value, sem_t **sem);
int				init_philos(t_game *game, t_philo **philos);
int				init_eats(size_t num, char ***names, sem_t ***eats);

/*
**init_game_utils.c - functions for initialisation help
*/

char			*get_name_eat_s_i(char *prefix, size_t i);
int				check_args(int argc, char **argv);

/*
**thread.c - functions for creation detaching and joining threads
*/

int				init_thread_detach(pthread_t *thread,
									void *(*rtn) (void *), void *args);
int				create_philo_processes(t_philo *philo, t_game *game,
										size_t num, size_t begin_i);
int				wait_philo_processes(t_game *game, size_t num);

/*
**routine.c - functions wich exucuting in threads
*/

void			*start_routine(void *args);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			*monitor_death(void *args);
void			*monitor_num_eat(void *args);

/*
**close_game.c - functions closing philosphers
*/

int				close_eats(size_t num, char **names, sem_t **eats);
int				close_one_sem(char *name, sem_t *sem);

/*
**print.c - functions info printing in STDOUT
*/

void			print_error(char *error);
int				print_action_wrap(t_philo *philo, char *action);
void			print_action(size_t time, long num, char *action);

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
unsigned int	ft_str_to_num(const char *str);
char			*ft_uitoa(size_t num);
int				ft_isdigit(int ch);
size_t			ft_strlen(char *str);

#endif
