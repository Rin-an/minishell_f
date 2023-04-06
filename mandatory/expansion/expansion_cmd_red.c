/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_cmd_red.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:55:37 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/10 01:49:12 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_expansion(t_simple_cmd **cmd, t_env **env, char **last_env)
{
	(*cmd)->inside_quotes = qoutes_status(((*cmd)->command));
	word_expansion(&((*cmd)->command), env, last_env, 0);
}

void	check_word_expand_redtion(int redirection, char **expanded, \
		char **word, char **string)
{
	if (redirection == 1)
	{
		if (*expanded != NULL && (*expanded)[0] != '\0')
		{
			*string = *expanded;
		}
		else
		{
			*string = ft_strdup(*word);
		}
	}
	else
	{
		*string = *expanded;
	}
	free(*word);
}

void	redirection_expansion(t_simple_cmd **cmd, t_env **env, char **last_env)
{
	t_redirection	*redis;
	int				here_doc_quotes;

	redis = NULL;
	redis = (*cmd)->redirections;
	while (redis)
	{
		if (redis->file_name)
		{
			redis->inside_quotes = qoutes_status(redis->file_name);
			if (redis->inside_quotes != 0)
				word_expansion(&redis->file_name, env, last_env, 0);
			else
				word_expansion(&redis->file_name, env, last_env, 1);
		}
		if (redis->delimiter)
		{
			here_doc_quotes = qoutes_status(redis->delimiter);
			if (here_doc_quotes != 0)
				here_doc_expansion(&redis->delimiter, 0);
			else
				here_doc_expansion(&redis->delimiter, 1);
		}
		redis = redis->next;
	}
}
