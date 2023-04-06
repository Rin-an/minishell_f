/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_arg_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 06:12:34 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/09 06:16:15 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	chiffre_count(unsigned int nb)
{
	int	i;

	i = 1;
	while (nb / 10 != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*int_to_str(int nb)
{
	int		i;
	int		length;
	char	*s;

	i = 0;
	length = 0;
	s = NULL;
	if (nb == 0)
		return (ft_strdup("0"));
	else
	{
		length = chiffre_count(nb);
		s = (char *)malloc(sizeof(length + 1));
		s[length] = '\0';
		length--;
		while (nb / 10 != 0)
		{
			s[length] = (nb % 10) + '0';
			nb = nb / 10;
			length--;
		}
		s[length] = (nb % 10) + '0';
		return (s);
	}
}
