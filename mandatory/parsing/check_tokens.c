/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:06:14 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/09 03:34:04 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_return(int quote)
{
	if (quote != 0)
		return (1);
	else
		return (0);
}

int	check_quotes(char *word)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (word[i])
	{
		if (quote == 0 && word[i] == 34)
			quote = first_d_quote(&i);
		else if (quote == 0 && word[i] == '\'')
			quote = first_s_quote(&i);
		else if (quote == 2 && word[i] == 34)
			close_d_quote(&i, &quote);
		else if (quote == 1 && word[i] == '\'')
			close_s_quote(&i, &quote);
		else
			i++;
	}
	return (quote_return(quote));
}

int	check_first_token(t_token *tokens_list, t_token *first_token, int *status)
{
	int	res;

	res = 0;
	if (first_token->type == PIPE)
	{
		display_syntax_error(first_token);
		clear_list(tokens_list);
		res = 1;
		*status = 258;
	}
	else if (first_token->type == NL)
	{
		clear_list(tokens_list);
		*status = 0;
		res = 1;
	}
	return (res);
}

int	check_next_pipe(t_token *tokens_list, t_token *token, int *status)
{
	int	res;

	res = 0;
	if (token->type == PIPE)
	{
		display_syntax_error(token);
		clear_list(tokens_list);
		*status = 258;
		res = 1;
	}
	else if (token->type == NL)
	{
		ft_putstr_fd("minishell: syntax error multiple line not allowed\n", 1);
		clear_list(tokens_list);
		*status = 258;
		res = 1;
	}
	return (res);
}

int	check_word(t_token *tokens_list, t_token *token, int *status)
{
	int	res;

	res = 0;
	if (check_quotes(token->value))
	{
		ft_putstr_fd("minishell: syntax error multiple line not allowed\n", 1);
		clear_list(tokens_list);
		*status = 258;
		res = 1;
	}
	return (res);
}
