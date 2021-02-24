/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:08:10 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/25 00:40:28 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

int check_arg(char *arg)
{
	int i;

	i = 0;
	while (ft_isdigit(arg[i]))
		i++;
	if (i > 0 && arg[i] == '\0')
		return (OK);
	return (KO);
}

int check_argv(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (check_arg(argv[i]) == KO)
			return (KO);
		i++;
	}
	return (OK);
}

int parse_args(int argc, char **argv, t_args *args)
{
	if (check_argv(argv) == KO)
		return (KO);
	args->num_philos = ft_atoui(argv[1]);
	args->time_to_die = ft_atoui(argv[2]);
	args->time_to_die = ft_atoui(argv[3]);
	args->time_to_die = ft_atoui(argv[4]);
	args->times_must_eat = argc == 6 ? ft_atoui(argv[5]) : -1;	
	return (OK);
}
