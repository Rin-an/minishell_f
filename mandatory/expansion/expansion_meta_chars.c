/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_meta_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:01:28 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/10 05:29:53 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	meta_chars_quotes(char *str, int *i, char **expanded, char *exit_status)
{
	if (ft_isdigit(str[*i + 1]))
		ft_digit_env(str, i, expanded);
	else if (str[*i + 1] == '?')
		ft_expand_exit_status(i, expanded, exit_status);
	else if (str[*i + 1] && str[*i + 1] != '\"' && \
		str[*i + 1] != ' ')
		ft_skip_characters_env_not_exist(str, i);
	else
		get_dollar_sign(str, i, expanded);
}

void	ft_skip_characters_non_env_variable(char *str, int *i, \
			char **expanded, int inside_quotes)
{
	char	*tmp1;
	char	*tmp;
	int		end_of_string;

	end_of_string = 0;
	tmp = NULL;
	tmp1 = NULL;
	end_of_string = check_end_of_string(str[*i + 1], inside_quotes);
	if (end_of_string)
	{
		tmp = *expanded;
		tmp1 = ft_substr(str, *i, 1);
		*expanded = ft_strjoin(*expanded, tmp1);
		free(tmp);
		free(tmp1);
		(*i)++;
	}
	else
		while (ft_isalpha(str[*i]) || str[*i] == '$')
			(*i)++;
}

void	meta_chars_expansion(char *str, int *i, char **expanded, \
			char *exit_status)
{
	if (str[*i + 1] != '"')
	{
		if (str[*i + 1] && (ft_isdigit(str[*i + 1])))
			ft_digit_env(str, i, expanded);
		else if (str[*i + 1] == '?')
			ft_expand_exit_status(i, expanded, exit_status);
		else if (str[*i + 1])
			ft_skip_characters_env_not_exist(str, i);
		else
			get_dollar_sign(str, i, expanded);
	}
	else
		(*i)++;
}

void	ft_skip_characters_env_not_exist(char *str, int *i)
{
	if (str[*i] == '$')
		(*i)++;
	while (ft_isalpha(str[*i]) || ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
}
