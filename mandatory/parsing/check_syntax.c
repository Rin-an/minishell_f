/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:55:48 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/09 04:22:19 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token(t_token *tokens_list, t_token *token, int *status)
{
	int	res;

	res = 0;
	if (token->type == NONE)
		res = check_first_token(tokens_list, token->next, status);
	else if (token->type == GREAT || token->type == DOUBLE_GREAT
		|| token->type == LESS || token->type == HERE_DOC)
		res = check_red(tokens_list, token->next, status);
	else if (token->type == PIPE)
		res = check_next_pipe(tokens_list, token->next, status);
	else if (token->type == WORD)
		res = check_word(tokens_list, token, status);
	return (res);
}

int	check_syntax_error(t_token *tokens_list, int *status)
{
	int		res;
	t_token	*temp;

	res = 0;
	temp = tokens_list;
	while (temp->type != NL)
	{
		if (temp->type == WORD && temp->next->type == NL)
		{
			res = check_word(tokens_list, temp, status);
			if (res)
				break ;
		}
		else
		{
			res = check_token(tokens_list, temp, status);
			if (res)
				break ;
		}
		temp = temp->next;
	}
	return (res);
}
