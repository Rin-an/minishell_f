/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:18:19 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/09 05:54:23 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd	*cmd;

	cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->command = NULL;
	cmd->next = NULL;
	cmd->args = NULL;
	cmd->redirections = NULL;
	return (cmd);
}

t_simple_cmd	*command_args_insertion(t_simple_cmd **cmd,
		t_token *token)
{
	t_args	*tmp;

	tmp = NULL;
	if ((*cmd)->command == NULL)
		(*cmd)->command = ft_strdup(token->value);
	else
	{
		if ((*cmd)->args == NULL)
			(*cmd)->args = arg_creation(token->value);
		else
		{
			tmp = arg_creation(token->value);
			arg_insertion((*cmd)->args, tmp);
		}
	}
	return (*cmd);
}

t_simple_cmd	*simple_cmd_creation(t_token **tokens)
{
	t_simple_cmd	*cmd;
	int				r;

	r = 0;
	cmd = init_simple_cmd();
	while ((*tokens)->type != PIPE && (*tokens)->type != NL)
	{
		if ((*tokens)->type == GREAT || (*tokens)->type == DOUBLE_GREAT
			|| (*tokens)->type == LESS || (*tokens)->type == HERE_DOC)
		{
			cmd->redirections = redirection_insertion(cmd->redirections,
					tokens, r);
			r++;
		}
		else if ((*tokens)->type == WORD)
		{
			cmd = command_args_insertion(&cmd, *tokens);
			(*tokens) = (*tokens)->next;
		}
		else
			(*tokens) = (*tokens)->next;
	}
	return (cmd);
}

void	simple_cmd_insertion(t_simple_cmd *head, t_simple_cmd *current_cmd)
{
	t_simple_cmd	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = current_cmd;
}
