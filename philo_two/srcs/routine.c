/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:03:51 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/01 20:19:36 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

void	*monitor_death(void *args)
{
	t_philo		*philo;
	size_t		time_to_die;
	size_t		diff_time;

	philo = (t_philo *)args;
	time_to_die = philo->args->time_to_die;
	while (*philo->status != KO)
	{
		if (sem_wait(philo->eat_s))
			*philo->status = KO;
		diff_time = get_difftime(philo->time_last_eat);
		if (diff_time > time_to_die)
		{
			print_action_wrap(philo, DIED);
			*philo->status = KO;
			sem_post(philo->eat_s);
			break ;
		}
		if (sem_post(philo->eat_s))
			*philo->status = KO;
		usleep(100);
	}
	return (NULL);
}

void	*monitor_num_eat(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (*philo->status != KO)
	{
		if (philo->num_eat >= philo->args->need_num_eat)
		{
			*philo->num_philos_have_eaten += 1;
			if (*philo->num_philos_have_eaten >= philo->args->num_philos)
				*philo->status = KO;
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

void	sleeping(t_philo *philo)
{
	print_action_wrap(philo, SLEEP);
	sleep_for(philo->args->time_to_sleep);
}

void	eating(t_philo *philo)
{
	if (sem_wait(philo->forks_s) ||
		print_action_wrap(philo, TAKE) ||
		sem_wait(philo->forks_s) ||
		print_action_wrap(philo, TAKE))
		*philo->status = KO;
	if (*philo->status != KO)
	{
		if (sem_wait(philo->eat_s))
			*philo->status = KO;
		print_action_wrap(philo, EAT);
		philo->time_last_eat = get_currtime();
		sleep_for(philo->args->time_to_eat);
		if (sem_post(philo->eat_s))
			*philo->status = KO;
		philo->num_eat++;
	}
	if (sem_post(philo->forks_s) ||
		sem_post(philo->forks_s))
		*philo->status = KO;
}

void	*start_routine(void *args)
{
	pthread_t	death;
	pthread_t	num_eat;
	t_philo		*philo;

	philo = (t_philo *)args;
	if (init_thread_detach(&death, monitor_death, args) == KO ||
		(philo->args->need_num_eat > 0 &&
		init_thread_detach(&num_eat, monitor_num_eat, args) == KO))
		*philo->status = KO;
	while (*philo->status != KO)
	{
		eating(philo);
		sleeping(philo);
		print_action_wrap(philo, THINK);
	}
	return (NULL);
}
