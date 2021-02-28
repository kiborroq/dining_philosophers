/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:29:09 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/01 01:37:30 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

char	*get_name_eat_s_i(char *prefix, size_t i)
{
	char	*suffix;
	size_t	prefix_len;
	size_t	suffix_len;
	char	*name;

	if (!(suffix = ft_uitoa(i + 1)))
		return (NULL);
	prefix_len = ft_strlen(prefix);
	suffix_len = ft_strlen(suffix);
	if (!(name = malloc(prefix_len + suffix_len + 1)))
		return (NULL);
	while (*prefix)
		*name++ = *prefix++;
	while (*suffix)
		*name++ = *suffix++;
	*name = '\0';
	return (name - prefix_len - suffix_len);
}

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
		tmp[i].forks_s = game->forks_s;
		tmp[i].printer_s = game->printer_s;
		tmp[i].args = &game->args;
		tmp[i].status = &game->status;
		tmp[i].begin_time = &game->begin_time;
		tmp[i].num_philos_have_eaten = &game->num_philos_have_eaten;
		if ((philos[i]->name = get_name_eat_s_i(PREFIX_EAT_S_, i)) == NULL ||
			init_one_sem(philos[i]->name, VALBINARY_S, &tmp[i].eat_s) == KO)
			return (KO);
		i++;
	}
	*philos = tmp;
	return (OK);
}

int	init_one_sem(char *name, size_t value, sem_t **sem)
{
	if ((*sem = sem_open(name, O_CREAT, S_IRWXU, value)) == SEM_FAILED)
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
	args->num_philos = ft_str_to_num(argv[1]);
	args->time_to_die = ft_str_to_num(argv[2]);
	args->time_to_eat = ft_str_to_num(argv[3]);
	args->time_to_sleep = ft_str_to_num(argv[4]);
	args->need_num_eat = argc == 6 ? (long)ft_str_to_num(argv[5]) : -1;
	if (!args->num_philos || !args->time_to_die || !args->need_num_eat)
		return (KO);
	return (OK);
}
