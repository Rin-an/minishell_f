/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:55:29 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 07:52:40 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exit_args(char *value)
{
	int		i;
	char	*error;
	long	status;

	i = -1;
	if (value[++i] == '-')
		i++;
	while (value[i])
	{
		if (ft_isdigit(value[i]) == 0)
		{
			error = ft_strjoin("exit: ", value);
			error = ft_strjoin(error, ":numeric argument required");
			exit(print_error(error, errno, 1));
		}
		i++;
	}
	status = ft_atoi(value);
	if (i == 0)
		return (status);
	return (status);
}

int	ft_exit(t_args *args)
{
	int		status;
	char	*error;

	if (!g_info.inchild)
		printf("exit\n");
	if (!args)
		exit(0);
	status = check_exit_args(args->value);
	if (args->next)
	{
		error = ft_strjoin("exit: ", "too many arguments");
		return (print_error(error, 1, 1));
	}
	exit(status);
}
