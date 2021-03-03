/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:53:04 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/03 19:49:36 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

int	close_eats(size_t num, char **names, sem_t **eats)
{
	size_t	i;

	i = 0;
	while (i < num && names[i])
	{
		if (close_one_sem(names[i], eats[i]) == KO)
			return (KO);
		free(names[i]);
		i++;
	}
	free(names);
	free(eats);
	return (OK);
}

int	close_one_sem(char *name, sem_t *sem)
{
	if (sem_close(sem) ||
		sem_unlink(name))
		return (KO);
	return (OK);
}
