/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:55:29 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/03 21:32:01 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

int		init_thread_detach(pthread_t *thread, void *(*rtn) (void *), void *args)
{
	if (pthread_create(thread, NULL, rtn, args) ||
		pthread_detach(*thread))
		return (KO);
	return (OK);
}

void	kill_processes(pid_t *pids, size_t num)
{
	size_t i;

	i = 0;
	while (i < num)
	{
		kill(pids[i], SIGTERM);
		i++;
	}
}

int		wait_philo_processes(t_game *game, size_t num)
{
	size_t	i;
	int		exit_status;

	i = 0;
	while (i < num)
	{
		waitpid(-1, &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		if (exit_status == KILL_ALL)
		{
			kill_processes(game->pids, num);
			return (OK);
		}
		i++;
	}
	return (OK);
}

int		create_philo_processes(t_philo *philo, t_game *game,
								size_t num, size_t begin_i)
{
	size_t i;

	i = begin_i;
	while (i < num)
	{
		philo->time_last_eat = game->begin_time;
		if (!(game->pids[i] = fork()))
		{
			philo->i = i;
			philo->eat_s = game->eats_s[i];
			start_routine((void *)(philo));
		}
		else if (game->pids[i] < 0)
			return (KO);
		usleep(50);
		i += 2;
	}
	return (OK);
}
