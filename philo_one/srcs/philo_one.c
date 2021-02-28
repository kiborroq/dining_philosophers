/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:10:25 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/28 22:14:02 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

void	close_game(t_game *game)
{
	if (game->forks_m)
		close_forks(game->args.num_philos, game->forks_m);
	if (game->printer_m)
		close_one_mutex(game->printer_m);
	if (game->philos)
		free(game->philos);
}

void	simulate_game(t_game *game, t_philo *philos, long num_philos)
{
	game->begin_time = get_currtime();
	if (create_philo_threads(philos, num_philos, FIRST) == KO ||
		create_philo_threads(philos, num_philos, SECOND) == KO ||
		join_philo_threads(philos, num_philos) == KO)
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
	if (init_forks(game->args.num_philos, &game->forks_m) == KO ||
		init_one_mutex(&game->printer_m) == KO ||
		init_philos(game, &game->philos) == KO)
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
