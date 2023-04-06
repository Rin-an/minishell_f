/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:43:56 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 01:09:01 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_here_doc(int sig)
{
	(void)sig;
	exit(130);
}

void	here_doc_signal(void)
{
	rl_catch_signals = 1;
	signal(SIGINT, manage_here_doc);
	signal(SIGQUIT, SIG_IGN);
}
