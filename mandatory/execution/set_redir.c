/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:59:13 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 06:33:02 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	keep_standard(t_exec *exec)
{
	if (exec->std[3])
	{
		exec->std[0] = dup(0);
		exec->std[1] = dup(1);
		exec->std[2] = dup(2);
		exec->std[3] = 0;
	}
	else
	{
		dup2(exec->std[0], 0);
		dup2(exec->std[1], 1);
		dup2(exec->std[2], 2);
		exec->std[3] = 1;
	}
}

int	input_redir(t_exec *exec, t_redirection *redir)
{
	exec->in_out[0] = open(redir->file_name, O_RDONLY);
	if (exec->in_out[0] < 0)
		return (file_err_type(redir));
	if (dup2(exec->in_out[0], 0) < 0)
		return (print_error(strerror(errno), 1, 0));
	close(exec->in_out[0]);
	return (0);
}

int	trunc_redir(t_exec *exec, t_redirection *redir)
{
	exec->in_out[1] = open(redir->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->in_out[1] < 0)
		return (file_err_type(redir));
	if (dup2(exec->in_out[1], 1) < 0)
		return (print_error(strerror(errno), 1, 0));
	close(exec->in_out[1]);
	return (0);
}

int	append_redir(t_exec *exec, t_redirection *redir)
{
	exec->in_out[1] = open(redir->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (exec->in_out[1] < 0)
		return (file_err_type(redir));
	if (dup2(exec->in_out[1], 1) < 0)
		return (print_error(strerror(errno), 1, 0));
	close(exec->in_out[1]);
	return (0);
}

int	set_redir(t_redirection *redir, t_exec *exec)
{
	if (here_doc(&redir, exec))
		return (1);
	while (redir)
	{
		if (redir->type == RE_LESS)
		{
			if (input_redir(exec, redir))
				return (1);
		}
		else if (redir->type == RE_GREAT)
		{
			if (trunc_redir(exec, redir))
				return (1);
		}
		else if (redir->type == RE_DOUBLE_GREAT)
		{
			if (append_redir(exec, redir))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
