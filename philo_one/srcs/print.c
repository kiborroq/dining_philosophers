/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:03:42 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/28 22:24:53 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

int		print_action_wrap(t_philo *philo, char *action)
{
	size_t	diff_time;

	if (*philo->status != KO)
	{
		diff_time = get_difftime(*philo->begin_time);
		pthread_mutex_lock(philo->printer_m);
		print_action(diff_time, philo->i + 1, action);
		pthread_mutex_unlock(philo->printer_m);
	}
	return (0);
}

void	print_action(size_t time, long num, char *action)
{
	printf("%lu %ld %s\n", time, num, action);
}

void	print_error(char *error)
{
	while (*error)
	{
		write(STDERR, error, 1);
		error++;
	}
	write(STDERR, "\n", 1);
}
