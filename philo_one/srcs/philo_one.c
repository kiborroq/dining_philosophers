/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:10:25 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/25 00:57:58 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

int	init_philos(t_game *game, t_philo **philos,
				t_mutex *forks, t_mutex *printer)
{
	t_philo	*tmp;
	long	i;

	if (!(tmp = (t_philo *)ft_calloc(game->num_philos, sizeof(t_philo))))
	{
		*philos = NULL;
		return (KO);
	}
	i = 0;
	while (i < game->args.num_philos)
	{
		tmp[i].i = i;
		tmp[i].l_fork = forks + i;
		tmp[i].r_fork = forks + i + 1;
		tmp[i].printer = printer;
		tmp[i].args = &game->args;
		tmp[i].status = &game->status;
		i++;
	}
	tmp[i].r_fork = forks + 0;
	*philos = tmp;
	return (OK);
}

int	init_forks(long num_forks, t_mutex **forks)
{
	long i;

	i = 0;
	if (!(*forks = (t_mutex *)ft_calloc(game->num_philos, sizeof(t_mutex))))
		return (KO);
	while (i < num_forks)
	{
		if (pthread_mutex_init(*forks + i, NULL) == KO)
			return (KO);
		i++;
	}
	return (OK);
}

int	init_printer(t_mutex **printer)
{
	if (!(*printer = (t_mutex *)ft_calloc(1, sizeof(t_mutex))))
		return (KO);
	if (pthread_mutex_init(*printer, NULL) == KO)
		return (KO);
	return (OK);
}

void	*start_routine(void *args)
{
	return (NULL);
}

int	init_game(t_game *game)
{
	if (init_forks(game->args.num_philos, &game->forks) == KO ||
		init_printer(&game->printer) == KO ||
		init_philos(game, &game->philos, game->forks, game->printer == KO)
		return (KO);
	return (OK);
}

int	create_threads(long num_threads, t_philo *philos, int mode)
{
	long	i;

	if (mode == END)
		return (OK);
	i = mode;
	while (i < num_threads)
	{
		if (pthread_create(philos[i].thread, NULL, start_routine, philos + i) == KO)
		{
			philos->status = KO;
			return (KO);
		}
		i += 2;
	}
	return (init_threads(num_threads, philos, mode + 1));
}

int	simulate_game()
{
	create_threads(game->args.num_philos, game->philos, FIRST) == KO)
}

int main(int argc, char **argv)
{
	t_game game;

	if (argc < 5 || > 6)
		print_error(ARG_NUM_ERROR);
	else if (parse_args(argc, argv, &game.args) == KO)
		print_error(ARG_FORMAT_ERROR);
	else if (init_game(&game) == KO)
		print_error(PHILOS_INIT_ERROR);
	else
		simulate_game();
	close_game(&game);
	return (0);
}
