/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 05:24:34 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 07:51:57 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute(char *cmd, t_args *args, t_env *env)
{
	int	cmd_pid;
	int	status;

	cmd_pid = fork();
	if (cmd_pid == 0)
	{
		if (execve(cmd, args_list_to_char(cmd, args), \
				env_list_to_char(env)) < 0)
			exit(print_error(strerror(errno), errno, 0));
	}
	else if (cmd_pid < 0)
		return (print_error(strerror(errno), errno, 0));
	else
	{
		waitpid(cmd_pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				printf("Quit :3\n");
			return (128 + WTERMSIG(status));
		}
	}
	return (1337);
}

void	set_fds(t_simple_cmd *cmd, t_env **head,
		t_exec *exec, int *command)
{
	int	i;

	i = -1;
	if (cmd->next)
		if (dup2(exec->in_out[*command + 1], 1) < 0)
			exit(1);
	if (*command != 0)
		if (dup2(exec->in_out[*command - 2], 0) < 0)
			exit(1);
	if (cmd->redirections != NULL)
	{
		if (set_redir(cmd->redirections, exec))
			exit(1);
	}
	while (++i < (exec->smpl_cmd_count * 2))
		close(exec->in_out[i]);
	exit(is_builtin(cmd, head));
}

int	wait_and_close(t_pipe_line *cmd, t_exec *exec)
{
	int	i;
	int	status;

	i = -1;
	while (++i < (cmd->simple_cmd_count * 2))
		close(exec->in_out[i]);
	i = -1;
	while (++i < cmd->simple_cmd_count + 1)
	{
		waitpid(exec->pid_tab[i], &status, 0);
		exec->r = WEXITSTATUS(status);
	}
	return (exec->r);
}

int	manage_pipes(t_pipe_line *cmds, t_env **env, t_exec *exec)
{
	t_simple_cmd	*tmp;
	int				command;
	int				i;

	i = -1;
	command = 0;
	tmp = cmds->child;
	cmds->simple_cmd_count--;
	exec->smpl_cmd_count = cmds->simple_cmd_count;
	while (tmp)
	{
		g_info.inchild = 1;
		g_info.has_del = 0;
		exec->pid_tab[++i] = fork();
		if (g_info.no_fork)
			exit(1);
		if (exec->pid_tab[i] == -1)
			return (print_error(strerror(errno), errno, 0));
		else if (exec->pid_tab[i] == 0)
			set_fds(tmp, env, exec, &command);
		tmp = tmp->next;
		command += 2;
		keep_standard(exec);
	}
	return (wait_and_close(cmds, exec));
}
