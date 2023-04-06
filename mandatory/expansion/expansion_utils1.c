/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:33:49 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/08 03:04:03 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_dollar_sign(char *str, int *i, char **expanded)
{
	char	*tmp1;
	char	*tmp;

	tmp1 = *expanded;
	tmp = ft_substr(str, *i, 1);
	*expanded = ft_strjoin(*expanded, tmp);
	free(tmp1);
	free(tmp);
	(*i)++;
}

void	ft_expand_exit_status(int *i, char **expanded, char *exit_status)
{
	char	*tmp1;
	char	*tmp;

	tmp = exit_status;
	tmp1 = *expanded;
	*expanded = ft_strjoin(*expanded, tmp);
	free(tmp1);
	*i += 2;
}

void	ft_digit_env(char *str, int *i, char **expanded)
{
	char	*tmp1;
	char	*tmp;

	if (str[*i + 1] == '0')
	{
		tmp1 = *expanded;
		tmp = ft_strdup("minishell");
		*expanded = ft_strjoin(*expanded, tmp);
		free(tmp1);
		free(tmp);
	}
	*i += 2;
}

int	qoutes_status(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			return (1);
		}
		else if (str[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

void	tilda_expansion(char **string)
{
	char	*tmp;
	int		len;
	char	*tmp1;
	char	*word;

	len = 0;
	word = *string;
	if (word[0] == '~' && (word[1] == '\0' || word[1] == '/'))
	{
		tmp = word;
		if (word[1] == '\0')
			word = ft_strdup("$HOME");
		else if (word[1] == '/')
		{
			len = ft_strlen(word);
			tmp1 = ft_substr(word, 1, len - 1);
			free(word);
			tmp = ft_strdup("$HOME");
			word = ft_strjoin(tmp, tmp1);
			free(tmp1);
		}
		free(tmp);
		tmp = NULL;
	}
	*string = word;
}
