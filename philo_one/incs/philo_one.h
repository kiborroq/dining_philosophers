/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:59:17 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/25 00:45:44 by kiborroq         ###   ########.fr       */
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

# define ARG_NUM_ERROR "Number of arguments isn't valid!"
# define ARG_FORMAT_ERROR "Fpormat of arguments isn't valid!"
# define PHILOS_INIT_ERROR "Error during philosophers initialisation!"
# define OK 1
# define KO -1
# define FIRST 0
# define SECOND 1
# define END 2

typedef pthread_mutex_t t_mutex;

typedef struct		s_args
{
	long			num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			times_must_eat;
}					t_args;

typedef struct		s_philo
{
	long			i;
	size_t			time_since_eat;
	int				has_died;
	int				*status;
	t_mutex			*l_fork;
	t_mutex			*r_fork;
	t_mutex			*printer;
	t_args			*args;
	pthread_t		*thread;
}					t_philo;

typedef struct		s_game
{
	int				status;
	t_args			args;
	t_mutex			*forks;
	t_mutex			*printer;
	t_philo			*philos;
	pthread_t		*threads;
}					t_game;

int					parse_args(int argc, char **argv, t_inf *inf);
int					check_argv(int argc, char **argv);
int					check_arg(char *arg);

void				*ft_calloc(size_t nmemb, size_t size);
unsigned int		ft_atoui(const char *str)

#endif