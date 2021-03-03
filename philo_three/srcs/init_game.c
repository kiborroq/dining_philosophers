/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:29:09 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/03 21:27:54 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

int	init_philos(t_game *game, t_philo **philos)
{
	t_philo	*tmp;

	if (!(tmp = (t_philo *)malloc(1 * sizeof(t_philo))))
		return (KO);
	ft_bzero(tmp, sizeof(t_philo));
	tmp->forks_s = game->forks_s;
	tmp->printer_s = game->printer_s;
	tmp->args = &game->args;
	tmp->status = &game->status;
	tmp->begin_time = &game->begin_time;
	tmp->num_philos_have_eaten = &game->num_philos_have_eaten;
	*philos = tmp;
	return (OK);
}

int	init_eats(size_t num, char ***names, sem_t ***eats)
{
	sem_t	**eats_tmp;
	char	**names_tmp;
	size_t	i;

	if (!(eats_tmp = (sem_t **)malloc(num * sizeof(sem_t *))))
		return (KO);
	ft_bzero(eats_tmp, num * sizeof(sem_t *));
	if (!(names_tmp = (char **)malloc(num * sizeof(char *))))
	{
		free(eats_tmp);
		return (KO);
	}
	ft_bzero(names_tmp, num * sizeof(char *));
	i = 0;
	while (i < num)
	{
		if ((names_tmp[i] = get_name_eat_s_i(PREFIX_EAT_S_, i)) == NULL ||
			init_one_sem(names_tmp[i], VALBINARY_S, &eats_tmp[i]) == KO)
			break ;
		i++;
	}
	*names = names_tmp;
	*eats = eats_tmp;
	return (OK);
}

int	init_one_sem(char *name, size_t value, sem_t **sem)
{
	sem_unlink(name);
	if ((*sem = sem_open(name, O_CREAT, S_IRWXU, value)) == SEM_FAILED)
		return (KO);
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
