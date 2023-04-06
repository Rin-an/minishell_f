/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:17:33 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/09 05:57:12 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipe_line	*init_pipe_line(void)
{
	t_pipe_line		*pipe_line;

	pipe_line = (t_pipe_line *)malloc(sizeof(t_pipe_line));
	if (!pipe_line)
		return (NULL);
	pipe_line->child = NULL;
	pipe_line->simple_cmd_count = 0;
	return (pipe_line);
}

t_pipe_line	*reset_pipe_line_head(t_pipe_line **pipe_line, t_simple_cmd *head)
{
	(*pipe_line)->child = head;
	return (*pipe_line);
}

t_pipe_line	*pipeline_creation(t_token **tokens)
{
	t_pipe_line		*pipe_line;
	t_simple_cmd	*head;
	t_simple_cmd	*current_cmd;

	pipe_line = init_pipe_line();
	current_cmd = NULL;
	head = NULL;
	while ((*tokens)->type != NL)
	{
		if (head == NULL)
		{
			head = simple_cmd_creation(tokens);
			pipe_line->simple_cmd_count += 1;
		}
		else
		{
			if ((*tokens)->type == NL)
				break ;
			(*tokens) = (*tokens)->next;
			current_cmd = simple_cmd_creation(tokens);
			simple_cmd_insertion(head, current_cmd);
			pipe_line->simple_cmd_count += 1;
		}
	}
	return (reset_pipe_line_head(&pipe_line, head));
}
