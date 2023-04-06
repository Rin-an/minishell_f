/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 05:57:01 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/09 06:02:27 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipe_line	*ft_parser(t_token *tokens_list, int *status)
{
	t_pipe_line		*command_list;

	command_list = NULL;
	if (!check_syntax_error(tokens_list, status))
		command_list = pipeline_creation(&tokens_list);
	return (command_list);
}
