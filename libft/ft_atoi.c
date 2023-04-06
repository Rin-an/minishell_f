/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 21:21:47 by ssadiki           #+#    #+#             */
/*   Updated: 2021/12/30 22:05:38 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	size_t		s;
	size_t		i;
	size_t		nb;

	i = 0;
	s = 1;
	nb = 0;
	while (is_space(str[i]) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		nb *= 10;
		nb += str[i] - 48;
		if (str[i + 1] < '0' || str[i + 1] > '9')
			break ;
		i++;
	}
	return ((int) s * nb);
}
