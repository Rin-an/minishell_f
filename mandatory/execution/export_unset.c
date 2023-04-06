/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:48:44 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 08:13:12 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_args(t_env *env)
{
	t_env	*sorted;
	t_env	*tmp;

	sorted = sort_env(env);
	tmp = sorted;
	while (sorted)
	{
		printf("declare -x ");
		printf("%s=\"", sorted->key);
		if (!sorted->value)
			printf("\"\n");
		else
			printf("%s\"\n", sorted->value);
		sorted = sorted->next;
	}
	destroy_env(&tmp);
	return (0);
}

void	join_value(t_env **env, t_env *replace, char **split)
{
	replace = find_env(*env, split[0]);
	if (!replace)
		add_new_env(env, init_env_values(ft_strdup(split[0]), \
				ft_strdup(split[1])));
	else
		update_env(env, replace->key, ft_strjoin(replace->value, split[1]));
}

void	add_replace_value(t_env **env, t_args *args)
{
	t_env	*replace;
	char	**split;
	int		i;

	split = ft_split(args->value, '=');
	i = ft_strlen(split[0]);
	if (split[0][--i] == '+')
	{
		split[0][i] = 0;
		replace = NULL;
		join_value(env, replace, split);
	}
	else
	{
		replace = find_env(*env, split[0]);
		if (!replace)
			add_new_env(env, init_env_values(ft_strdup(split[0]), \
					ft_strdup(split[1])));
		else
			update_env(env, replace->key, split[1]);
	}
	free_arg(split);
}

int	export(t_args *args, t_env **env)
{
	int		r;
	char	*error;
	t_args	*tmp;

	r = 0;
	if (!args)
		return (no_args(*env));
	tmp = args;
	while (tmp)
	{
		if (!tmp->value)
			r = print_error("export: `': not a valid identifier", 1, 0);
		else if ((!(tmp->value[0] == '_') && !ft_isalpha(tmp->value[0])))
		{
			error = ft_strjoin("export : `", tmp->value);
			error = ft_strjoin(error, "': not a valid identifier");
			r = print_error(error, 1, 1);
			free(error);
		}
		else
			add_replace_value(env, tmp);
		tmp = tmp->next;
	}
	return (r);
}

int	unset(t_env **env, t_args *args)
{
	while (args)
	{
		if (!args->value)
			return (print_error("unset: `': not a valid identifier", 1, 0));
		else
			remove_env(env, find_env(*env, args->value));
		args = args->next;
	}
	return (0);
}
