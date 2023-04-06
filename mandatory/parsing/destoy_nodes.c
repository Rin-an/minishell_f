/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destoy_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:17:47 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/01 21:08:18 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_red(t_redirection *red)
{
	t_redirection	*current_red;
	t_redirection	*parent_red;

	parent_red = red;
	while (parent_red)
	{
		current_red = parent_red;
		parent_red = parent_red->next;
		if (current_red->file_name)
			free(current_red->file_name);
		if (current_red->delimiter)
			free(current_red->delimiter);
		free(current_red);
	}
}

void	clear_simple_cmd(t_simple_cmd *cmd)
{
	t_args	*head;
	t_args	*current_arg;

	head = NULL;
	current_arg = NULL;
	if (cmd->command)
		free(cmd->command);
	head = cmd->args;
	while (head != NULL)
	{
		current_arg = head;
		head = head->next;
		free(current_arg->value);
		current_arg->value = NULL;
		free(current_arg);
	}
	current_arg = NULL;
	if (cmd->redirections)
		clear_red(cmd->redirections);
	cmd->redirections = NULL;
	free(cmd);
}

void	clear_pipe_line(t_pipe_line *pipe_line)
{
	t_simple_cmd	*current_cmd;
	t_simple_cmd	*parent_cmd;

	parent_cmd = pipe_line->child;
	while (parent_cmd)
	{
		current_cmd = parent_cmd;
		parent_cmd = parent_cmd->next;
		clear_simple_cmd(current_cmd);
		current_cmd = NULL;
	}
	free(pipe_line);
	pipe_line = NULL;
}
