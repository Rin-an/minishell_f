/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 04:41:58 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/08 21:30:24 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env(t_env **env, t_env *remove)
{
	t_env	*head;
	t_env	*tmp;

	if (!*env || !remove)
		return ;
	tmp = NULL;
	head = *env;
	while (head)
	{
		if (head->next && head->next == remove)
		{
			tmp = head->next;
			break ;
		}
		head = head->next;
	}
	head->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int	ft_lstsize(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (i);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_list_to_char(t_env *env)
{
	char	**s;
	int		i;
	char	*tmp;

	if (!env)
		return (NULL);
	s = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!s)
		return (NULL);
	i = -1;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		s[++i] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	s[++i] = NULL;
	return (s);
}
