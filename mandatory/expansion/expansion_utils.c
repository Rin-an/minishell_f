/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:23:54 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/10 01:45:38 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_variable_value(char *env_variable, t_env **env)
{
	t_env	*tmp;
	int		j;
	char	*str;

	str = env_variable + 1;
	j = 1;
	while (!ft_isalnum(env_variable[0]) && (ft_isalpha(env_variable[j])
			|| env_variable[j] == '_' || ft_isalnum(env_variable[j])))
		j++;
	str = ft_substr(env_variable, 1, j - 1);
	tmp = find_env(*env, str);
	if (str)
		free(str);
	if (tmp)
		return (ft_strdup(tmp->value));
	else
		return (NULL);
}

int	check_end_of_string(char str, int inside_quotes)
{
	if (inside_quotes == 0)
	{
		if (!str)
			return (1);
	}
	else
	{
		if (str == '\"')
			return (1);
	}
	return (0);
}
