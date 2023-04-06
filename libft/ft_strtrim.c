/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 00:08:59 by ssadiki           #+#    #+#             */
/*   Updated: 2021/12/28 00:43:45 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_occ(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i++])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ns;
	int		s;
	int		e;

	if (!s1 || !set)
		return (NULL);
	s = 0;
	e = ft_strlen(s1) - 1;
	while (ft_occ(set, s1[s]))
		s++;
	while (ft_occ(set, s1[e]) && e >= 0)
		e--;
	if (e < 0)
		return (ft_strdup(""));
	ns = malloc(e - s + 2);
	if (!ns)
		return (NULL);
	ft_strlcpy(ns, s1 + s, e - s + 2);
	return (ns);
}
