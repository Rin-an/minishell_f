/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 06:36:49 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 06:38:24 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dollar_sign_sequence(char *str, int *i, char **expanded)
{
	char	*tmp1;
	char	*tmp;
	int		j;

	(*i)++;
	j = *i;
	while (str[j] == '$')
		j++;
	tmp1 = *expanded;
	tmp = ft_substr(str, *i, j - *i);
	*expanded = ft_strjoin(*expanded, tmp);
	free(tmp1);
	free(tmp);
	*i += 1;
}
