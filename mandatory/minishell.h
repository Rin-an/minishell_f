/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:21:34 by ssadiki           #+#    #+#             */
/*   Updated: 2022/11/10 06:39:37 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	NONE,
	WORD,
	GREAT,
	LESS,
	DOUBLE_GREAT,
	HERE_DOC,
	PIPE,
	NL,
}	t_token_type;

typedef struct s_tokenizer
{
	char				*value;
	int					index;
	enum e_token_type	type;
	struct s_tokenizer	*next;
}	t_token;

typedef enum e_redirection_type{
	RE_GREAT,
	RE_DOUBLE_GREAT,
	RE_LESS,
	D_HERE_DOC,
}			t_redirection_type;

typedef struct s_redirection
{
	int						index;
	t_redirection_type		type;
	int						inside_quotes;
	char					*file_name;
	char					*delimiter;
	struct s_redirection	*next;
}				t_redirection;

typedef struct s_args{
	int				inside_quotes;
	char			*value;
	struct s_args	*next;
}				t_args;

typedef struct s_simple_cmd
{
	int					inside_quotes;
	char				*command;
	t_args				*args;
	t_redirection		*redirections;
	struct s_simple_cmd	*next;
}				t_simple_cmd;

typedef struct s_pipe_line
{
	int					simple_cmd_count;
	t_simple_cmd		*child;
}				t_pipe_line;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}	t_env;

typedef struct s_exec
{
	int		*in_out;
	int		std[4];
	int		smpl_cmd_count;
	int		r;
	int		*pid_tab;
}	t_exec;

typedef struct s_expansion
{
	char	*word;
	char	*expanded;
	char	*tmp1;
	char	*tmp;
}	t_expansion;

typedef struct s_gbl_info
{
	int		inchild;
	int		no_fork;
	int		has_del;
	char	**free;
}	t_g_info;

t_g_info	g_info;

//ENV
t_env			*init_env(char **envp);
char			*get_path(t_env *env);
void			add_new_env(t_env **env, t_env *new);
t_env			*init_env_values(char *key, char *value);
t_env			*find_env(t_env *env, char *var);
void			update_env(t_env **env, char *key, char *value);
t_env			*sort_env(t_env *env);
void			remove_env(t_env **env, t_env *remove);
char			**env_list_to_char(t_env *env);

//UTILS
int				ft_dstrlen(char **s);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				print_error(char *str, int exit_s, int fr);
char			**ft_split_export(char const *s, char c);
char			**args_list_to_char(char *cmd, t_args *args);
int				file_err_type(t_redirection *redir);
void			here_doc_signal(void);

//FREE
void			destroy_env(t_env **env);
void			free_arg(char **arg);
int				free_exec(t_exec *exec);
void			unlink_file(void);

//EXECUTION
int				execute_all(t_pipe_line *cmds, t_env **env);
int				manage_pipes(t_pipe_line *cmds, t_env **env, t_exec *exec);
void			execute_file(t_simple_cmd *cmd, t_env *env, char *path, \
					int *r);				
int				execute(char *cmd, t_args *args, t_env *env);
int				execute_pipes(t_simple_cmd *cmds, char **env);
void			keep_standard(t_exec *exec);
int				set_redir(t_redirection *redir, t_exec *exec);
int				input_redir(t_exec *exec, t_redirection *redir);
int				trunc_redir(t_exec *exec, t_redirection *redir);
int				append_redir(t_exec *exec, t_redirection *redir);
int				here_doc(t_redirection **redir, t_exec *exec);
int				path_or_exec(t_simple_cmd *cmd, t_env *env);
int				wait_exec(int cmd_pid);

//BUILT-INS
int				is_builtin(t_simple_cmd *cmd, t_env **env);
int				cd(t_simple_cmd *cmd, t_env **env);
int				echo(t_args *args);
int				get_env(t_env *env);
int				pwd(t_env *env);
int				export(t_args *args, t_env **env);
int				unset(t_env **env, t_args *args);
int				ft_exit(t_args *args);

//LEXER
t_token			*ft_lexer(char *line);
void			ft_get_word(t_token *tokens_list, char *line, int *table);
void			ft_meta_char(t_token *tokens_list,
					char *line, int *j, int *index);
void			clear_list(t_token *tokens_list);
void			print_tokens(t_token *tokens_list);
void			addnew_token(t_token *token_list, t_token_type type,
					char *content, int i);
char			*get_words(char *line, int *j, char *word, int *quoting);

//ERROR

int				first_d_quote(int *index);
int				first_s_quote(int *index);
void			close_d_quote(int *index, int *quote);
void			close_s_quote(int *index, int *quote);
int				check_first_token(t_token *tokens_list,
					t_token *first_token, int *status);
int				check_next_pipe(t_token *tokens_list,
					t_token *token, int *status);
int				check_word(t_token *tokens_list,
					t_token *token, int *status);
int				check_tokn_next_semi(t_token *tokens_list,
					t_token *token, int *status);
int				check_syntax_error(t_token *tokens_list, int *status);
int				check_token(t_token *tokens_list,
					t_token *token, int *status);
int				check_quotes(char *word);
int				quote_return(int quote);
int				check_red(t_token *tokens_list, t_token *token, int *status);
void			display_syntax_error(t_token *token);

//PARSING

t_pipe_line		*ft_parser(t_token *tokens_list, int *status);
void			clear_pipe_line(t_pipe_line *cmd_list);
int				check_syntax_error(t_token *tokens_list, int *status);
void			ft_print_pipeline_cmd(t_pipe_line *pipe_line);
void			ft_print_simple_cmd(t_simple_cmd *cmd);
void			clear_red(t_redirection *red);
void			clear_simple_cmd(t_simple_cmd *cmd);
t_simple_cmd	*simple_cmd_creation(t_token **tokens);
void			simple_cmd_insertion(t_simple_cmd *head,
					t_simple_cmd *current_cmd);
t_redirection	*redirection_insertion(t_redirection *redirection,
					t_token **tokens, int index);
t_args			*arg_creation(char *value);
void			arg_insertion(t_args *head, t_args *current_args);
int				check_tokn_next_semi(t_token *tokens_list, t_token *token,
					int *status);
int				check_word(t_token *tokens_list, t_token *token,
					int *status);
int				check_last_word_token(t_token *tokens_list, t_token *token,
					int *status);
int				check_first_token(t_token *tokens_list, t_token *first_token,
					int *status);
int				check_redirection(t_token *tokens_list, t_token *token,
					int *status);
int				check_next_pipe(t_token *tokens_list, t_token *token,
					int *status);
void			ft_print_systax_error(t_token *token);
t_pipe_line		*pipeline_creation(t_token **tokens);

//EXPANSION

void			expansion(t_pipe_line *pipe_line, t_env **env, char **last_env);
void			simple_cmd_expansion(t_simple_cmd **cmd, t_env **env, \
					char **last_env);
void			arguments_expansion(t_simple_cmd **cmd, t_env **env, \
					char **last_env);
void			word_expansion(char **string, t_env **env_list, \
					char **last_env, int red);
void			tilda_expansion(char **string);
int				qoutes_status(char *str);
void			single_quotes_remove(char *str, int *i, char **expanded_word);
void			get_charachter(char *str, int *i, char **expanded_word);
char			*double_quotes_expansion(t_expansion expd, int *i, \
					t_env **env_list, char **last_env);
char			*double_quotes_remove(char *word, int *i, \
					t_env **env_list, char **last_env);
void			env_var_expansion(t_expansion *expd, int *j, \
					t_env **env_list, char **last_env);
void			env_value_sub(char *str, int *i, char **expanded, \
					char **env_value);
void			ft_skip_characters_env_not_exist(char *str, int *i);
void			meta_chars_expansion(char *str, int *i, \
					char **expanded, char *exit_status);
void			ft_digit_env(char *str, int *i, char **expanded);
void			ft_skip_characters_non_env_variable(char *str, int *i, \
					char **expanded, int inside_quotes);
void			meta_chars_quotes(char *str, int *i, \
					char **expanded, char *exit_status);
void			ft_expand_exit_status(int *i, char **expanded, \
					char *exit_status);
void			get_dollar_sign(char *str, int *i, char **expanded);
void			ft_expande_redirection(t_simple_cmd **cmd, \
					t_env **env, char **last_env);
void			check_word_expand_redtion(int redirection, \
					char **expanded, char **word, char **string);
void			ft_expand_command(t_simple_cmd **cmd, \
					t_env **env, char **last_env);
int				check_end_of_string(char str, int inside_quotes);
char			*get_env_variable_value(char *env_variable, t_env **env);
void			redirection_expansion(t_simple_cmd **cmd, \
					t_env **env, char **last_env);
void			command_expansion(t_simple_cmd **cmd, \
					t_env **env, char **last_env);
void			here_doc_quotes_remove(char *str, int *i, char **expanded_word);
void			here_doc_expansion(char **string, int red);
void			dollar_sign_sequence(char *str, int *i, char **expanded);

//EXIT

char			*int_to_str(int n);
char			*the_arg(char **split);
char			*ex_last_arg_ret(char *argument_value);
char			*export_last_arg(t_args **args, \
					t_pipe_line **current_pipe_line);
char			*last_arg(t_pipe_line *current_pipe_line);

#endif
