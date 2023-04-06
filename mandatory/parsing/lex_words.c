/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:00:48 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/01 21:08:39 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*zero_quoted_word(char *str, int *i)
{
	char	*word;
	int		j;

	j = *i;
	while (str[j] && !ft_strchr("\t \'\"<>|", str[j]))
		j++;
	word = ft_substr(str, *i, j - *i);
	*i = j;
	return (word);
}

static char	*d_quoted_word(char *str, int *i, int j)
{
	char	*word;

	word = NULL;
	while (str[j] && str[j] != '"')
		j++;
	word = ft_substr(str, *i, j - *i + 1);
	*i = j + 1;
	return (word);
}

static char	*s_quoted_word(char *str, int *i, int quote_status)
{
	int		j;
	char	*word;

	j = *i;
	word = NULL;
	if (quote_status == 1)
	{
		j++;
		while (str[j] && str[j] != '\'')
			j++;
		word = ft_substr(str, *i, j - *i + 1);
		*i = j + 1;
		return (word);
	}
	else if (quote_status == 2)
		return (d_quoted_word(str, i, ++j));
	return (word);
}

char	*get_words(char *str, int *j, char *word, int *quote_status)
{
	char	*temp;
	char	*temp1;

	if (*quote_status == 0)
	{
		temp = word;
		temp1 = zero_quoted_word(str, j);
		word = ft_strjoin(word, temp1);
		free(temp);
		free(temp1);
	}
	else if (*quote_status > 0)
	{
		temp = word;
		temp1 = s_quoted_word(str, j, *quote_status);
		word = ft_strjoin(word, temp1);
		free(temp1);
		free(temp);
	}
	return (word);
}
