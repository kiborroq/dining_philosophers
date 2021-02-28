/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:29:09 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/28 20:08:28 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

int	init_philos(t_game *game, t_philo **philos)
{
	t_philo	*tmp;
	size_t	i;

	if (!(tmp = (t_philo *)malloc(game->args.num_philos * sizeof(t_philo))))
		return (KO);
	ft_bzero(tmp, game->args.num_philos * sizeof(t_philo));
	i = 0;
	while (i < game->args.num_philos)
	{
		tmp[i].i = i;
		tmp[i].leftfork_m = game->forks_m + i;
		tmp[i].rightfork_m = game->forks_m + i + 1;
		tmp[i].printer_m = game->printer_m;
		tmp[i].args = &game->args;
		tmp[i].status = &game->status;
		tmp[i].begin_time = &game->begin_time;
		tmp[i].num_philos_have_eaten = &game->num_philos_have_eaten;
		tmp[i].thereis_died = &game->thereis_died;
		if (pthread_mutex_init(&tmp[i].eat_m, NULL))
			return (KO);
		i++;
	}
	tmp[i - 1].rightfork_m = game->forks_m + 0;
	*philos = tmp;
	return (OK);
}

int	init_forks(size_t num_forks, t_mutex **forks_m)
{
	size_t	i;
	t_mutex	*tmp;

	i = 0;
	if (!(tmp = (t_mutex *)malloc(num_forks * sizeof(t_mutex))))
		return (KO);
	while (i < num_forks)
	{
		if (pthread_mutex_init(tmp + i, NULL))
			return (KO);
		i++;
	}
	*forks_m = tmp;
	return (OK);
}

int	init_one_mutex(t_mutex **mutex)
{
	if (!(*mutex = (t_mutex *)malloc(sizeof(t_mutex))))
		return (KO);
	if (pthread_mutex_init(*mutex, NULL))
		return (KO);
	return (OK);
}

int	check_args(int argc, char **argv)
{
	int		i;
	char	*arg;

	i = 1;
	while (i < argc)
	{
		arg = argv[i];
		if (*arg == '\0')
			return (KO);
		while (*arg)
		{
			if (!ft_isdigit(*arg))
				return (KO);
			arg++;
		}
		i++;
	}
	return (OK);
}

int	init_args(int argc, char **argv, t_args *args)
{
	if (check_args(argc, argv) == KO)
		return (KO);
	args->num_philos = ft_atoui(argv[1]);
	args->time_to_die = ft_atoui(argv[2]);
	args->time_to_eat = ft_atoui(argv[3]);
	args->time_to_sleep = ft_atoui(argv[4]);
	args->need_num_eat = argc == 6 ? (long)ft_atoui(argv[5]) : -1;
	if (!args->num_philos || !args->time_to_die || !args->need_num_eat)
		return (KO);
	return (OK);
}
