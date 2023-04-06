/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:45:47 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/10 05:34:02 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_value_sub(char *str, int *i, char **expanded, char **env_value)
{
	char	*temp;

	temp = *expanded;
	*expanded = ft_strjoin(*expanded, *env_value);
	free(temp);
	free(*env_value);
	if (str[*i] == '$')
		(*i)++;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
}

void	here_doc_quotes_remove(char *str, int *i, char **expanded_word)
{
	int		j;
	char	*tmp;
	char	c;
	char	*temp;

	temp = *expanded_word;
	c = str[*i];
	(*i)++;
	j = *i;
	while (str[j] != c)
		j++;
	tmp = ft_substr(str, *i, j - *i);
	*expanded_word = ft_strjoin(*expanded_word, tmp);
	free(temp);
	free(tmp);
	*i = j + 1;
}

void	here_doc_expansion(char **string, int red)
{
	t_expansion	expd;
	int			i;

	i = 0;
	expd.word = *string;
	expd.expanded = NULL;
	while (expd.word[i])
	{
		if (expd.word[i] == '\'' || expd.word[i] == '"')
			here_doc_quotes_remove(expd.word, &i, &expd.expanded);
		else
			get_charachter(expd.word, &i, &expd.expanded);
	}
	check_word_expand_redtion(red, &expd.expanded, &expd.word, string);
}

void	word_expansion(char **string, t_env **env_list, char **last_env, \
			int red)
{
	t_expansion	expd;
	int			i;

	i = 0;
	expd.word = *string;
	expd.expanded = NULL;
	tilda_expansion(&expd.word);
	while (expd.word[i])
	{
		if (expd.word[i] == '\'')
			single_quotes_remove(expd.word, &i, &expd.expanded);
		else if (expd.word[i] == '"')
			expd.expanded = double_quotes_expansion(expd, &i, env_list,
					last_env);
		else if (expd.word[i] == '$')
			env_var_expansion(&expd, &i, env_list, last_env);
		else
			get_charachter(expd.word, &i, &expd.expanded);
	}
	check_word_expand_redtion(red, &expd.expanded, &expd.word, string);
}

void	arguments_expansion(t_simple_cmd **cmd, t_env **env, char **last_env)
{
	t_args			*args;

	args = (*cmd)->args;
	while (args)
	{
		args->inside_quotes = qoutes_status(args->value);
		word_expansion(&args->value, env, last_env, 0);
		args = args->next;
	}
}
