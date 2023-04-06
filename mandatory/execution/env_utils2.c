/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:52:53 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 08:11:07 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_env(t_env *env, char *var)
{
	while (env)
	{
		if (!ft_strcmp(var, env->key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->key, key)))
			break ;
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = ft_strdup(value);
	free(value);
}

void	switch_values(t_env *env, t_env *s)
{
	char	*key;
	char	*value;

	key = s->key;
	s->key = env->key;
	env->key = key;
	value = s->value;
	s->value = env->value;
	env->value = value;
}

t_env	*copy_env(t_env *env)
{
	t_env	*cpy;

	if (!env)
		return (NULL);
	cpy = NULL;
	while (env)
	{
		add_new_env(&cpy, init_env_values(ft_strdup(env->key), \
				ft_strdup(env->value)));
		env = env->next;
	}
	return (cpy);
}

t_env	*sort_env(t_env *env)
{
	t_env	*s;
	t_env	*r;
	t_env	*tmp;

	r = copy_env(env);
	tmp = r;
	while (tmp)
	{
		s = tmp;
		while (s)
		{
			if (ft_strcmp(tmp->key, s->key) > 0)
				switch_values(tmp, s);
			s = s->next;
		}
		tmp = tmp->next;
	}
	return (r);
}
