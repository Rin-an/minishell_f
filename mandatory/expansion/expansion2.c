/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 06:01:26 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 01:50:41 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	simple_cmd_expansion(t_simple_cmd **cmd, t_env **env, char **last_env)
{
	t_args			*args;

	args = NULL;
	arguments_expansion(cmd, env, last_env);
	if ((*cmd)->command)
		command_expansion(cmd, env, last_env);
	redirection_expansion(cmd, env, last_env);
}

void	expansion(t_pipe_line *pipe_line, t_env **env, char **last_env)
{
	t_simple_cmd	*cmd;
	t_simple_cmd	*head;

	cmd = NULL;
	head = NULL;
	if (pipe_line)
		head = pipe_line->child;
	while (head)
	{
		cmd = head;
		simple_cmd_expansion(&cmd, env, last_env);
		head = head->next;
	}
}
