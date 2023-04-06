/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:44:39 by ssadiki           #+#    #+#             */
/*   Updated: 2022/10/25 10:34:58 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ns;
	size_t		i;
	size_t		l;

	i = 0;
	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l)
		return (ft_strdup(""));
	else if (len > l - start)
		len = l - start;
	ns = (char *) malloc(sizeof(char) * len + 1);
	if (!ns)
		return (NULL);
	while (i < len)
		ns[i++] = s[start++];
	ns[i] = '\0';
	return (ns);
}
