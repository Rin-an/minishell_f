/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:18:00 by fabou-za          #+#    #+#             */
/*   Updated: 2022/11/09 06:02:52 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_red_type(t_token_type type, t_redirection *red)
{
	if (type == GREAT)
		red->type = RE_GREAT;
	else if (type == DOUBLE_GREAT)
		red->type = RE_DOUBLE_GREAT;
	else if (type == LESS)
		red->type = RE_LESS;
}

t_redirection	*redirection_creation(t_token **tokens, int index)
{
	t_redirection	*redirection;
	int				flag;

	flag = 0;
	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redirection)
		return (NULL);
	redirection->index = index;
	redirection->next = NULL;
	redirection->file_name = NULL;
	redirection->delimiter = NULL;
	get_red_type((*tokens)->type, redirection);
	if ((*tokens)->type == HERE_DOC)
	{
		redirection->type = D_HERE_DOC;
		flag = 1;
	}
	(*tokens) = (*tokens)->next;
	if (flag == 1)
		redirection->delimiter = ft_strdup((*tokens)->value);
	else
		redirection->file_name = ft_strdup((*tokens)->value);
	(*tokens) = (*tokens)->next;
	return (redirection);
}

t_redirection	*redirection_insertion(t_redirection *redirection,
		t_token **tokens, int index)
{
	t_redirection	*tmp;

	tmp = NULL;
	if (redirection == NULL)
		redirection = redirection_creation(tokens, index);
	else
	{
		tmp = redirection;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = redirection_creation(tokens, index);
	}
	return (redirection);
}

void	arg_insertion(t_args *head, t_args *current_args)
{
	t_args	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = current_args;
}

t_args	*arg_creation(char *value)
{
	t_args	*arg;

	arg = (t_args *)malloc(sizeof(t_args));
	arg->value = ft_strdup(value);
	arg->next = NULL;
	arg->inside_quotes = 0;
	return (arg);
}
