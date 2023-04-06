/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:15:18 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/09 06:15:24 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*the_arg(char	**split_ret)
{
	char	*l_arg;

	l_arg = ft_strdup(split_ret[0]);
	free(split_ret[0]);
	free(split_ret);
	return (l_arg);
}

char	*ex_last_arg_ret(char *argument_value)
{
	char	**split_ret;

	split_ret = ft_split(argument_value, '=');
	if (split_ret[0] == NULL)
		split_ret[0] = ft_strdup("=");
	else
	{
		if (split_ret[0][0] != argument_value[0])
		{
			free(split_ret[0]);
			split_ret[0] = ft_strdup(argument_value);
		}
	}
	free(split_ret[1]);
	if (split_ret[0])
		return (the_arg(split_ret));
	else
	{
		free(split_ret);
		return (NULL);
	}
}

char	*export_last_arg(t_args	**args,
		t_pipe_line **p)
{
	while ((*args)->next != NULL)
		(*args) = (*args)->next;
	if ((*p)->child->command
		&&!ft_strcmp((*p)->child->command, "export"))
		return (ex_last_arg_ret((*args)->value));
	else
	{
		if ((*args)->value)
			return (ft_strdup((*args)->value));
		else
		{
			if ((*p)->child->command)
				return (ft_strdup((*p)->child->command));
		}
	}
	return (NULL);
}

char	*last_arg(t_pipe_line *p)
{
	t_args	*args;

	if (p->child->next != NULL)
		return (NULL);
	else
	{
		args = p->child->args;
		if (args == NULL)
		{
			if (p->child->command)
				return (ft_strdup(p->child->command));
		}
		else
		{
			return (export_last_arg(&args, &p));
		}
	}
	return (NULL);
}
