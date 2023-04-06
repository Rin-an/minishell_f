/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 19:35:41 by ssadiki           #+#    #+#             */
/*   Updated: 2022/01/01 15:01:20 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long long n)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	i;
	long	m;
	size_t	len;

	m = n;
	len = ft_count(n);
	if (len == 0)
		len++;
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	i = 0;
	if (m < 0)
	{
		m *= -1;
		s[i++] = '-';
	}
	s[len] = '\0';
	while (len-- > i)
	{
		s[len] = (m % 10) + 48;
		m /= 10;
	}
	return (s);
}
