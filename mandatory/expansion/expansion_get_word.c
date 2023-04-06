/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_get_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:44:26 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/10 06:39:20 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_var_expansion(t_expansion *expd, int *j, t_env **env_list, \
			char **last_env)
{
	if (expd->word[*j + 1] && expd->word[*j + 1] == '$')
		dollar_sign_sequence(expd->word, j, &(expd->expanded));
	else
	{
		expd->tmp = get_env_variable_value(expd->word + *j, env_list);
		if (expd->tmp)
			env_value_sub(expd->word, j, &(expd->expanded), &(expd->tmp));
		else if (j == 0 || expd->word[*j - 1] != '$')
			meta_chars_quotes(expd->word, j, \
					&(expd->expanded), last_env[0]);
		else
			ft_skip_characters_non_env_variable(expd->word, j, \
					&(expd->expanded), 1);
	}
}

char	*double_quotes_remove(char *word, int *i, t_env **env_list, \
		char **last_env)
{
	t_expansion	expd;
	int			j;

	expd.expanded = NULL;
	j = *i + 1;
	expd.word = word;
	while (expd.word[j] != '"')
	{
		if (expd.word[j] == '$')
			env_var_expansion(&expd, &j, env_list, \
					last_env);
		else
			get_charachter(expd.word, &j, &expd.expanded);
	}
	j++;
	*i = j;
	return (expd.expanded);
}

char	*double_quotes_expansion(t_expansion expd, int *i, t_env **env_list, \
		char **last_env)
{
	char	*temp;

	temp = expd.expanded;
	expd.tmp = double_quotes_remove(expd.word, i, env_list, last_env);
	if (expd.tmp)
	{
		expd.expanded = ft_strjoin(expd.expanded, expd.tmp);
		free(temp);
		free(expd.tmp);
	}
	return (expd.expanded);
}

void	get_charachter(char *str, int *i, char **expanded_word)
{
	char	*temp;
	char	*tmp;

	tmp = *expanded_word;
	temp = ft_substr(str, *i, 1);
	*expanded_word = ft_strjoin(*expanded_word, temp);
	free(tmp);
	free(temp);
	(*i)++;
}

void	single_quotes_remove(char *str, int *i, char **expanded_word)
{
	int		j;
	char	*tmp;
	char	*temp;

	(*i)++;
	j = *i;
	while (str[j] != '\'')
		j++;
	temp = *expanded_word;
	tmp = ft_substr(str, *i, j - *i);
	*expanded_word = ft_strjoin(*expanded_word, tmp);
	free(temp);
	free(tmp);
	*i = j + 1;
}
