/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:59:44 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/07 04:42:42 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_list(t_token *list)
{
	t_token	*temp;

	temp = NULL;
	if (!list)
		return ;
	while ((list)->type != NL)
	{
		temp = list;
		list = (list)->next;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
	if ((list)->type == NL)
	{
		free((list)->value);
		(list)->value = NULL;
		free(list);
		list = NULL;
	}
}

t_token	*first_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->value = ft_strdup("NONE");
	new_token->next = NULL;
	new_token->type = NONE;
	new_token->index = 0;
	return (new_token);
}

void	addnew_token(t_token *token_list, t_token_type type, \
		char *content, int index)
{
	t_token	*temp;

	temp = token_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = (t_token *)malloc(sizeof(t_token));
	temp->next->index = index;
	temp->next->type = type;
	temp->next->value = content;
	temp->next->next = NULL;
}

/*
 * arr[3];
 * 0 = i  ; 1 = j ; index = 2
 * */

void	create_list(t_token *list, char *str)
{
	int	arr[3];

	arr[2] = 1;
	arr[0] = 0;
	while (str && str[arr[0]])
	{
		arr[1] = arr[0];
		while (str[arr[1]] == ' ' || str[arr[1]] == '\t')
			arr[1]++;
		if (ft_strchr("|><", str[arr[1]]) != NULL)
			ft_meta_char(list, str, &arr[1], &arr[2]);
		if (ft_strchr("\t <>|", str[arr[1]]) == NULL)
			ft_get_word(list, str, arr);
		arr[0] = arr[1];
	}
	addnew_token(list, NL, ft_strdup("newline"), arr[2]);
}

t_token	*ft_lexer(char *str)
{
	t_token	*list;

	list = NULL;
	list = first_token();
	create_list(list, str);
	return (list);
}
