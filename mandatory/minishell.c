/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:31:21 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 02:01:20 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
	}
	free(*env);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		if (g_info.inchild == 1)
			return ;
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_info.has_del)
			return ;
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

void	expand_and_execute(t_pipe_line *p, t_env **env, int *status)
{
	static char	*last_arg_exit_sts[2];

	if (last_arg_exit_sts[0])
		free(last_arg_exit_sts[0]);
	last_arg_exit_sts[0] = int_to_str(*status);
	expansion(p, env, last_arg_exit_sts);
	if (p)
	{
		if (last_arg_exit_sts[1])
			free(last_arg_exit_sts[1]);
		last_arg_exit_sts[1] = last_arg(p);
		*status = execute_all(p, env);
	}
}

void	ft_minishell(int *status, t_pipe_line *p, t_env **env)
{
	char	*s;
	t_token	*token_list;

	g_info.no_fork = 0;
	g_info.inchild = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	s = readline("minishell~");
	if (!s)
	{
		write(1, "exit\n", 5);
		exit(1);
	}
	if (*s)
		add_history(s);
	token_list = ft_lexer(s);
	p = ft_parser(token_list, status);
	expand_and_execute(p, env, status);
	free(s);
	if (p)
	{
		clear_list(token_list);
		clear_pipe_line(p);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			status;
	t_env		*env;
	t_pipe_line	*p;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	status = 0;
	p = NULL;
	rl_catch_signals = 0;
	while (1)
		ft_minishell(&status, p, &env);
	destroy_env(&env);
	return (0);
}
