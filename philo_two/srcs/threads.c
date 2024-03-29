/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:55:29 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/03 23:00:31 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

int	init_thread_detach(pthread_t *thread, void *(*rtn) (void *), void *args)
{
	if (pthread_create(thread, NULL, rtn, args) ||
		pthread_detach(*thread))
		return (KO);
	return (OK);
}

int	join_philo_threads(t_philo *philos, size_t num)
{
	size_t i;

	i = 0;
	while (i < num)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (KO);
		i++;
	}
	return (OK);
}

int	create_philo_threads(t_philo *philos, size_t num, size_t begin_i)
{
	size_t i;

	i = begin_i;
	while (i < num)
	{
		philos[i].time_last_eat = *philos->begin_time;
		if (pthread_create(&philos[i].thread, NULL,
							start_routine, (void*)(philos + i)))
			return (KO);
		usleep(50);
		i += 2;
	}
	return (OK);
}
