/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:41:02 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/01 21:57:59 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_option(char *arg)
{
	int	j;

	j = 0;
	while (arg[j] && arg[++j] == 'n')
		;
	if (!arg[j])
		return (0);
	return (1);
}

void	print_echo(t_args *args)
{
	while (args)
	{
		if (args->value)
			ft_putstr_fd(args->value, 1);
		if (args->next)
			ft_putchar_fd(' ', 1);
		args = args->next;
	}
}

int	echo(t_args *args)
{
	int	flag;

	flag = 1;
	if (!args)
	{
		printf("\n");
		return (0);
	}
	while (args && args->value && args->value[0] == '-')
	{
		if (!has_option(args->value))
		{
			flag = 0;
			args = args->next;
		}
		else
			break ;
	}
	print_echo(args);
	if (flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
