/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:02:43 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/24 19:36:48 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

void			ft_bzero(void *mem, size_t n)
{
	memset(mem, 0, n);
}

void			*ft_calloc(size_t nmemb, size_t size)
{
	void *mem;

	if (!nmemb || !size)
		mem = malloc(1);
	else
		mem = malloc(nmemb * size);
	if (!mem)
		return (0);
	ft_bzero(mem, nmemb * size);
	return (mem);
}

int				ft_isspace(int ch)
{
	if (ch == 32 || (ch > 8 && ch < 14))
		return (1);
	return (0);
}

int				ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

unsigned int	ft_atoui(const char *str)
{
	int				i;
	unsigned int	num;
	int				sign;

	i = 0;
	num = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}
