/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:08:37 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/09 06:02:01 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_d_quote(int *index)
{
	int	quote;

	quote = 0;
	quote += 2;
	(*index)++;
	return (quote);
}

int	first_s_quote(int *index)
{
	int	quote;

	quote = 0;
	quote += 1;
	(*index)++;
	return (quote);
}

void	close_d_quote(int *index, int *quote)
{
	*quote -= 2;
	(*index)++;
}

void	close_s_quote(int *index, int *quote)
{
	*quote -= 1;
	(*index)++;
}
