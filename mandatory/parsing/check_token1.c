/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:15:19 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/09 03:35:00 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(token->value, 1);
	ft_putstr_fd("'\n", 1);
}

int	check_red(t_token *tokens_list, t_token *token, int *status)
{
	int	res;

	res = 0;
	if (token->type != WORD)
	{
		display_syntax_error(token);
		clear_list(tokens_list);
		*status = 258;
		res = 1;
	}
	return (res);
}
