/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 04:00:57 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 01:31:18 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_new_input(t_exec *exec, t_redirection *redir, char *file)
{
	char	*str;

	while (1)
	{
		str = readline(">");
		if (!str || !ft_strcmp(str, redir->delimiter))
			exit(0);
		ft_putendl_fd(str, exec->in_out[0]);
		free(str);
	}
	if (str)
		free(str);
	redir->file_name = ft_strdup(file);
	redir->type = RE_LESS;
	return (0);
}

int	set_here_doc_input(t_exec *exec, t_redirection *redir)
{
	char	*file;

	file = ft_strdup("/tmp/tmp_file");
	here_doc_signal();
	exec->in_out[0] = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->in_out[0] < 0)
		return (print_error(strerror(errno), errno, 0));
	if (set_new_input(exec, redir, file))
		return (1);
	close(exec->in_out[0]);
	free(file);
	exit(1);
}

int	fork_here_doc(t_exec *exec, t_redirection *tmp)
{
	int	status;
	int	pid;

	g_info.has_del = 1;
	pid = fork();
	if (pid < 0)
		exit(print_error(strerror(errno), errno, 0));
	if (!pid)
		set_here_doc_input(exec, tmp);
	waitpid(pid, &status, 0);
	g_info.has_del = 0;
	return (WEXITSTATUS(status));
}

int	here_doc(t_redirection **redir, t_exec *exec)
{
	t_redirection	*tmp;

	tmp = *redir;
	while (tmp)
	{
		if (tmp->type == D_HERE_DOC)
		{
			fork_here_doc(exec, tmp);
			tmp->file_name = ft_strdup("/tmp/tmp_file");
			tmp->type = RE_LESS;
		}
		tmp = tmp->next;
	}
	return (0);
}
