/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:04:07 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/03 21:30:41 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

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
	{
		free(suffix);
		return (NULL);
	}
	while (*prefix)
		*name++ = *prefix++;
	while (*suffix)
		*name++ = *suffix++;
	*name = '\0';
	free(suffix - suffix_len);
	return (name - prefix_len - suffix_len);
}

int		check_args(int argc, char **argv)
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
