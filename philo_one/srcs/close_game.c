/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:53:04 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/01 01:15:58 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

int	close_forks(size_t num_forks, t_mutex *forks)
{
	size_t	i;

	i = 0;
	while (i < num_forks)
	{
		if (pthread_mutex_destroy(forks + i))
			return (KO);
		i++;
	}
	free(forks);
	return (OK);
}

int	close_one_mutex(t_mutex *mutex)
{
	if (pthread_mutex_destroy(mutex))
		return (KO);
	free(mutex);
	return (OK);
}
