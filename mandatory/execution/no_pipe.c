/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:00:05 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 08:01:25 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_executable_file(t_simple_cmd *cmd, t_env *env)
{
	struct stat	info;
	char		*error;

	if (stat(cmd->command, &info) == -1)
	{
		error = ft_strjoin(cmd->command, " : No such file or directory");
		return (print_error(error, 127, 1));
	}
	if (info.st_mode & S_IFDIR)
	{
		error = ft_strjoin(cmd->command, " : Is a directory");
		return (print_error(error, 126, 1));
	}
	if (!(info.st_mode & S_IXUSR))
	{
		error = ft_strjoin(cmd->command, " : Permission denied");
		return (print_error(error, 126, 1));
	}
	g_info.inchild = 1;
	return (execute(cmd->command, cmd->args, env));
}

int	search_file(t_simple_cmd *cmd, t_env *env)
{
	char	**paths;
	int		r;
	int		i;

	r = 1337;
	paths = ft_split(get_path(env), ':');
	if (!paths)
		return (is_executable_file(cmd, env));
	i = -1;
	while (paths[++i])
	{
		execute_file(cmd, env, paths[i], &r);
		free(paths[i]);
	}
	free(paths);
	return (r);
}

int	path_or_exec(t_simple_cmd *cmd, t_env *env)
{
	int		r;
	int		i;

	i = -1;
	if (ft_strchr(cmd->command, '/') || cmd->command[0] == '.')
		return (is_executable_file(cmd, env));
	else
	{
		r = search_file(cmd, env);
		if (r != 1337)
			return (r);
		return (print_error("command not found", 127, 0));
	}
	return (0);
}
