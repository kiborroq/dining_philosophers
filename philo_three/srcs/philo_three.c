/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:10:25 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/03 20:07:12 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

void	close_game(t_game *game)
{
	int	status;

	status = OK;
	if (game->forks_s && game->forks_s != SEM_FAILED)
		status = close_one_sem(FORKS_S, game->forks_s);
	if (status != KO && game->printer_s && game->printer_s != SEM_FAILED)
		status = close_one_sem(PRINTER_S, game->printer_s);
	if (status != KO && game->philos)
		status = close_eats(game->args.num_philos,
							game->names, game->eats_s);
	if (status != KO && game->pids)
		free(game->pids);
	if (status == KO)
		print_error(PHILOS_CLOSE_ERROR);
}

void	simulate_game(t_game *game, t_philo *philos, size_t num_philos)
{
	game->begin_time = get_currtime();
	if (create_philo_processes(philos, game, num_philos, FIRST) == KO ||
		create_philo_processes(philos, game, num_philos, SECOND) == KO ||
		wait_philo_processes(game, num_philos) == KO)
		print_error(PHILOS_SIMULATE_ERROR);
}

int		init_game(int argc, char **argv, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	if (argc < 5 || argc > 6)
	{
		print_error(ARG_NUM_ERROR);
		return (KO);
	}
	if (init_args(argc, argv, &game->args) == KO)
	{
		print_error(ARG_FORMAT_ERROR);
		return (KO);
	}
	if (init_one_sem(FORKS_S, game->args.num_philos, &game->forks_s) == KO ||
		init_one_sem(PRINTER_S, VALBINARY_S, &game->printer_s) == KO ||
		init_philos(game, &game->philos) == KO ||
		init_eats(game->args.num_philos, &game->names, &game->eats_s) == KO ||
		!(game->pids = (pid_t *)malloc(game->args.num_philos * sizeof(pid_t))))
	{
		print_error(PHILOS_INIT_ERROR);
		return (KO);
	}
	return (OK);
}

int		main(int argc, char **argv)
{
	t_game		game;

	if (init_game(argc, argv, &game) == OK)
		simulate_game(&game, game.philos, game.args.num_philos);
	close_game(&game);
	return (0);
}
