/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:27:30 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/09 18:18:54 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_pwd(t_env **env, char *cd)
{
	t_env	*replace;

	replace = find_env(*env, "PWD");
	update_env(env, "OLDPWD", replace->value);
	update_env(env, "PWD", cd);
}

int	change_dir(t_env **env, char *cd)
{
	char	*pwd;
	char	*error;

	if (chdir(cd) == -1)
	{
		error = ft_strjoin(cd, strerror(errno));
		print_error(ft_strjoin("cd :", error), 1, 1);
		free(error);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		error = ft_strjoin("cd: error retrieving current\
directory:\
getcwd: cannot access parent directories: ", strerror(errno));
		print_error(error, 1, 1);
	}
	else
		set_pwd(env, pwd);
	free(pwd);
	return (0);
}

int	check_pwd(t_env **env, char *cd)
{
	t_env	*check;

	check = find_env(*env, "PWD");
	if (!check)
		add_new_env(env, init_env_values("PWD", ""));
	check = find_env(*env, "OLDPWD");
	if (!check)
		add_new_env(env, init_env_values("OLDPWD", ""));
	if (!change_dir(env, cd))
		return (0);
	return (1);
}

int	cd(t_simple_cmd *cmd, t_env **env)
{
	char	*cd;
	t_env	*check;

	if (!cmd->args || !ft_strcmp(cmd->args->value, "~"))
	{
		check = find_env(*env, "HOME");
		if (!check)
			return (print_error("cd: HOME not set", 1, 0));
		cd = check->value;
	}
	else if (!(ft_strcmp(cmd->args->value, "-")))
	{
		check = find_env(*env, "OLDPWD");
		if (!check)
			print_error("cd: OLDPWD not set \n", 1, 0);
		printf("%s\n", check->value);
		cd = check->value;
	}
	else
		cd = cmd->args->value;
	if (check_pwd(env, cd))
		return (1);
	return (0);
}

int	pwd(t_env *env)
{
	char	*pwd;
	t_env	*search;

	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s\n", pwd);
	else
	{
		search = find_env(env, "PWD");
		if (search)
			printf("%s\n", search->value);
	}
	free(pwd);
	return (0);
}
