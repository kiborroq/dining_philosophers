/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:53:04 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/28 18:27:31 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

void	close_forks(size_t num_forks, t_mutex *forks)
{
	size_t	i;

	i = 0;
	while (i < num_forks)
	{
		pthread_mutex_destroy(forks + i);
		i++;
	}
	free(forks);
}

void	close_one_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex);
	free(mutex);
}
