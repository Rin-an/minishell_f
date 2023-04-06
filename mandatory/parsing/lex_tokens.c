/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:48:09 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/01 21:08:35 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_the_beginning_of_word(int c)
{
	if (c == 39)
		return (1);
	else if (c == 34)
		return (2);
	else
		return (0);
}

static void	add_token_and_increament_index(t_token *tokens_list, char *word,
			int *arr, int j)
{
	addnew_token(tokens_list, WORD, word, arr[2]);
	arr[1] = j;
	arr[2]++;
}

void	ft_get_word(t_token *tokens_list, char *str, int *arr)
{
	int		quote_status;
	char	*word;
	int		j;

	j = 0;
	quote_status = -1;
	word = NULL;
	j = arr[1];
	while (str[j])
	{
		quote_status = check_the_beginning_of_word(str[j]);
		if (quote_status == 0)
		{
			word = get_words(str, &j, word, &quote_status);
			if (ft_strchr("\t ><|", str[j]))
				break ;
		}
		else if (quote_status > 0)
		{
			word = get_words(str, &j, word, &quote_status);
			if (str[j] == ' ' || str[j] == '\t')
				break ;
		}
	}
	add_token_and_increament_index(tokens_list, word, arr, j);
}
