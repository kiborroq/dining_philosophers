/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:53:04 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/03 23:00:31 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

int	close_philos(size_t num_philos, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < num_philos)
	{
		if (close_one_sem(philos[i].name, philos[i].eat_s) == KO)
			return (KO);
		free(philos[i].name);
		i++;
	}
	free(philos);
	return (OK);
}

int	close_one_sem(char *name, sem_t *sem)
{
	if (sem_close(sem) ||
		sem_unlink(name))
		return (KO);
	return (OK);
}
