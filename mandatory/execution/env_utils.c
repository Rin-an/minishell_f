/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:39:55 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/08 06:14:47 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_env_values(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

void	add_new_env(t_env **env, t_env *new)
{
	t_env	*head;

	if (!new)
		return ;
	if (!env || !(*env))
	{
		*env = new;
		return ;
	}
	head = *env;
	while (head->next)
		head = head->next;
	head->next = new;
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	**split;
	int		i;

	if (!envp)
		return (NULL);
	i = -1;
	env = NULL;
	while (envp[++i])
	{
		split = ft_split(envp[i], '=');
		add_new_env(&env, init_env_values(split[0], split[1]));
		free(split);
	}
	return (env);
}

char	*get_path(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 4))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_env(t_env *env)
{
	while (env)
	{
		if (env->key != NULL && env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
