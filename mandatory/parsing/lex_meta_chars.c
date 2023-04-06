/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_meta_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:00:26 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/01 21:08:33 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_red(t_token *tokens_list, char *str, int *j, int *index)
{
	if ((str[*j] == '>' && str[*j + 1] == '>') || \
			(str[*j] == '<' && str[*j + 1] == '<'))
	{
		if (str[*j] == '>')
			addnew_token(tokens_list, DOUBLE_GREAT, ft_strdup(">>"), *index);
		else
			addnew_token(tokens_list, HERE_DOC, ft_strdup("<<"), *index);
		*j = *j + 2;
		(*index)++;
	}
	else if (str[*j] == '<' || str[*j] == '>')
	{
		if (str[*j] == '<')
			addnew_token(tokens_list, LESS, ft_strdup("<"), *index);
		else
			addnew_token(tokens_list, GREAT, ft_strdup(">"), *index);
		(*j)++;
		(*index)++;
	}
}

void	ft_meta_char(t_token *tokens_list, char *str, int *j, int *index)
{
	char	*token;

	if (str[*j] == '|')
	{
		token = ft_strdup("|");
		addnew_token(tokens_list, PIPE, token, *index);
		(*index)++;
		(*j)++;
	}
	else
		ft_red(tokens_list, str, j, index);
}
