/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:09:06 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/28 18:25:34 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

size_t	get_difftime(size_t time)
{
	size_t	currtime;

	currtime = get_currtime();
	return (currtime - time);
}

size_t	get_currtime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleep_for(size_t time)
{
	size_t end;

	end = get_currtime() + time;
	while (get_currtime() < end)
		usleep(1);
}
