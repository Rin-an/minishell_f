/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:57:30 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/09 00:32:12 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_exec(t_exec *exec)
{
	free(exec->in_out);
	free(exec->pid_tab);
	return (1);
}

void	unlink_file(void)
{
	if (g_info.has_del)
		unlink("/tmp/tmp_file");
	g_info.has_del = 0;
}
