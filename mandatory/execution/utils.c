/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:51:53 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/07 23:48:29 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *str, int exit_s, int fr)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	if (fr)
		free(str);
	return (exit_s);
}

int	ft_arg_lstsize(t_args *args)
{
	int	i;

	i = 0;
	if (!args)
		return (i);
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}

char	**args_list_to_char(char *cmd, t_args *args)
{
	char	**s;
	int		i;

	if (!cmd && !args)
		return (NULL);
	s = malloc(sizeof(char *) * (ft_arg_lstsize(args) + 2));
	if (!s)
		return (NULL);
	i = -1;
	s[++i] = ft_strdup(cmd);
	while (args)
	{
		s[++i] = ft_strdup(args->value);
		args = args->next;
	}
	s[++i] = NULL;
	g_info.free = s;
	return (s);
}

int	file_err_type(t_redirection *redir)
{
	struct stat	info;
	char		*error;

	if (!stat(redir->file_name, &info))
	{
		if (info.st_mode & S_IFDIR)
		{
			error = ft_strjoin(redir->file_name, " : Is a directory");
			return (print_error(error, 126, 1));
		}
		else if (!(info.st_mode & S_IXUSR))
		{
			error = ft_strjoin(redir->file_name, " : Permission denied");
			return (print_error(error, 126, 1));
		}
	}
	error = ft_strjoin(redir->file_name, " : No such file or directory");
	return (print_error(error, 127, 1));
}

void	free_arg(char **arg)
{
	int	i;

	i = -1;
	while (arg && arg[++i])
		free(arg[i]);
	free(arg);
}
