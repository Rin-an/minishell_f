/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:12:22 by ssadiki           #+#    #+#             */
/*   Updated: 2021/12/29 21:27:53 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s;
	size_t	d;
	size_t	i;
	size_t	j;

	s = ft_strlen(src);
	d = ft_strlen(dst);
	if (!dstsize)
		return (s);
	i = d;
	j = 0;
	if (dstsize <= d || dstsize == 0)
		return (s + dstsize);
	while (src[j] && i < dstsize - 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (s + d);
}
