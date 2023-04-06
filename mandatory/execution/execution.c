/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:42:46 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 08:02:21 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmp_cmd(char *cmd, char *str)
{
	int	i;

	i = -1;
	while (cmd[++i])
		cmd[i] = ft_tolower(cmd[i]);
	return (ft_strcmp(cmd, str));
}

int	is_builtin(t_simple_cmd *cmd, t_env **env)
{
	if (!cmp_cmd(cmd->command, "echo"))
		return (echo(cmd->args));
	else if (!cmp_cmd(cmd->command, "cd"))
		return (cd(cmd, env));
	else if (!cmp_cmd(cmd->command, "pwd"))
		return (pwd(*env));
	else if (!cmp_cmd(cmd->command, "export"))
		return (export(cmd->args, env));
	else if (!cmp_cmd(cmd->command, "unset"))
		return (unset(env, cmd->args));
	else if (!cmp_cmd(cmd->command, "env"))
		return (get_env(*env));
	else if (!cmp_cmd(cmd->command, "exit"))
		return (ft_exit(cmd->args));
	else
	{
		g_info.inchild = 1;
		return (path_or_exec(cmd, *env));
	}
}

int	init_exec(t_exec *exec, int count)
{
	int	i;

	exec->in_out = malloc(sizeof(int) * (count * 2));
	exec->pid_tab = malloc(sizeof(int) * (count + 1));
	if (!exec->pid_tab || !exec->in_out)
		return (1);
	exec->std[0] = 0;
	exec->std[1] = 0;
	exec->std[2] = 0;
	exec->std[3] = 1;
	exec->smpl_cmd_count = count;
	i = -1;
	while (++i < count)
	{
		if (pipe(exec->in_out + i * 2) < 0)
			return (print_error(strerror(errno), errno, 0));
	}
	return (0);
}

void	execute_file(t_simple_cmd *cmd, t_env *env, char *path, int *r)
{
	char		*file;
	char		*tmp;
	struct stat	info;

	tmp = ft_strjoin(path, "/");
	file = ft_strjoin(tmp, cmd->command);
	free(tmp);
	stat(file, &info);
	if (*r == 1337 && ((info.st_mode & S_IXUSR) > 0
			&& (info.st_mode & S_IFREG) > 0))
		*r = execute(file, cmd->args, env);
	free(file);
}

int	execute_all(t_pipe_line *cmds, t_env **env)
{
	t_exec			exec;
	int				r;

	if (init_exec(&exec, cmds->simple_cmd_count - 1))
		return (free_exec(&exec));
	keep_standard(&exec);
	r = 0;
	if (cmds->child->redirections)
	{
		if (set_redir(cmds->child->redirections, &exec))
		{
			keep_standard(&exec);
			return (free_exec(&exec));
		}
	}
	if (!(cmds->child->command || cmds->child->redirections))
		return (print_error("\0: command not found", 127, 0));
	if (cmds->simple_cmd_count > 1)
		r = manage_pipes(cmds, env, &exec);
	else if (cmds->child->command)
		r = is_builtin(cmds->child, env);
	keep_standard(&exec);
	free_exec(&exec);
	free_arg(g_info.free);
	return (r);
}
