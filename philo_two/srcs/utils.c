/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:02:43 by kiborroq          #+#    #+#             */
/*   Updated: 2021/03/03 23:00:31 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

void			ft_bzero(void *mem, size_t n)
{
	memset(mem, 0, n);
}

size_t			ft_strlen(char *str)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len])
		str_len++;
	return (str_len);
}

int				ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

char			*ft_uitoa(size_t num)
{
	size_t	sep;
	size_t	len;
	char	*num_str;
	size_t	i;

	sep = 1;
	len = 1;
	while (num / sep > 9)
	{
		len++;
		sep *= 10;
	}
	if (!(num_str = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		num_str[i] = num / sep + 48;
		num %= sep;
		sep /= 10;
		i++;
	}
	num_str[i] = '\0';
	return (num_str);
}

unsigned int	ft_str_to_num(const char *str)
{
	int				i;
	unsigned int	num;

	i = 0;
	num = 0;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}
