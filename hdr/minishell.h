/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlouaked <wlouaked@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:55:04 by wlouaked          #+#    #+#             */
/*   Updated: 2024/12/26 16:28:50 by wlouaked         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------------------------------------------------- */
/*                                   HEADERS                                  */
/* -------------------------------------------------------------------------- */

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define EXIT_GENERAL_ERROR 2
# define EXIT_CMD_NOT_EXECUT 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD_INTERRUPTED 130
# define EXIT_ERROR_FORMAT 258

# define S_U_EOF "unexpected EOF while looking for matching `''"
# define D_U_EOF "unexpected EOF while looking for matching `\"'"

/* -------------------------------------------------------------------------- */
/*                                GLOBALS VARIABLES                           */
/* -------------------------------------------------------------------------- */

extern int			g_flag_signal;

/* -------------------------------------------------------------------------- */
/*                                  STUCTURES                                 */
/* -------------------------------------------------------------------------- */

typedef enum e_type
{
	NONE,
	CMD,
	ARG,
	WORD,
	PIPE,
	SQUOTE,
	DQUOTE,
	OPERATOR_OUT,
	OPERATOR_IN,
	OPERATOR_APPEND,
	OPERATOR_HEREDOC,
	FILES,
	DOLLAR,
	END
}	t_type;

# define KEY 0
# define VALUE 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	char	*name;
	int		status;
	bool	is_child;
	t_env	*env;
}	t_data;

typedef struct s_files
{
	t_type			mode;
	char			*path;
	bool			remove_quotes;
	char			**heredoc;
	struct s_files	*next;
	struct s_files	*prev;
}					t_files;

typedef struct s_cmd
{
	char			*path;
	char			**arg;
	int				pipe_fd[2];
	char			*heredoc_name;
	int				heredoc_read;
	int				heredoc_write;
	int				in_fd;
	int				out_fd;
	pid_t			pid;
	t_files			*files;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_queue
{
	t_token	*first;
	t_token	*last;
}	t_queue;

typedef struct s_counter
{
	int	i;
	int	j;
	int	k;
}						t_counter;

/* -------------------------------------------------------------------------- */
/*                                 FUNCTIONS                                  */
/* -------------------------------------------------------------------------- */

t_data		*get_data(void);

// Garbage collector
void		ft_free(void *ptr);
void		*ft_malloc(size_t size_to_alloc);
void		lock(void *ptr);
void		unlock(void *ptr);
void		soft_clear(void);
void		clear_all(void);

// Signaux
void		set_data_signal(t_data *data);

// Tokenisation
bool		no_invalid_quotes(t_data *data, char *cmd_line);
bool		is_operator(char c);
bool		is_redirection(t_type type);
bool		is_operator_type(t_type type);
t_token		*tokenizer(char *cmd_line);
void		add_to_queue(t_queue *queue, char *content, t_type type);
void		add_operator(t_queue *queue, char *str, int *i);
void		skip_spaces(char *str, int *i);
t_type		affect_type(char *operator);

// Parser
t_cmd		*parser(t_token *queue);

int			ft_echo(int option, char **string, int fd);
int			ft_env(int fd);
int			ft_exit(char **arg, int last_status);
int			ft_pwd(int fd);
char		*get_echo_n_output(char *string);
char		*get_echo_output(char *string);
int			if_option_n(char *string);
int			is_white_space(int c);
int			is_white_space(int c);
int			isprint_expect_space(int c);
int			is_printable_in_string(char const *s);
char		*rm_white_space(const char *s);
long long	ft_atol(const char *nptr);
bool		is_long(char *arg);
char		**ft_strrdup(char **s);
int			ft_setenv(char *key, char *value);
char		*ft_set_var(const char *name, const char *value);
int			how_many_line_in_array(char **array);
int			add_line_to_array(char ***array, const char *name,
				const char *value);
char		**ft_strrdup(char **s);
char		*ft_getenv(const char *name);
int			ft_export(char **args);
int			ft_unset(char **args);
void		rm_line_to_array(char ***envp, const char *name);
int			ft_cd(char **path);
int			cd_in_home(char **args);
int			cd_towards_path(char **args);
int			check_var(char *string);
int			ft_check_first_char(char *string);
bool		ft_is_valid_var(char *string);
int			ft_minimal_env(char ***envp);
void		ft_set_env(char ***envp);
int			ft_open_files(t_cmd *cmd);
int			handler_in_operator(t_files *file);
int			handler_out_operator(t_files *file);;
t_files		*create_file_node(t_type mode, const char *path);
void		lst_file_add_back(t_files **lst, t_files *new);
int			valid_name_var(char *string);
void		free_cmd(t_cmd **cmds);
void		free_files(t_files **files);
void		ft_close_builtins_fd_backwards(t_files *file_table);
void		ft_close_builtins_fd(t_files *file_table);
int			check_built_in(char *cmd);
void		lst_file_add_back(t_files **file_table, t_files *new);
char		**strrdup_add_line(char **s, char *new);
int			handler_heredoc(t_cmd *cmd);
char		**strrdup_add_line(char **s, char *new);
int			ft_create_pipe(t_cmd *cmd);
void		ft_exec(t_cmd *cmd);
int			exec_cmd(t_cmd *cmd);
char		*ft_add_cmd_name(char *path, char *cmd);
void		find_cmd_path(t_cmd *cmd, char *relative_path);
void		ft_free_pt_char(char **ptr);
int			exec_builtins(t_cmd *cmd);
bool		has_echo_option(char **arg);
int			exec_child_builtins(t_cmd *cmd);
int			check_format_var(char *string);
char		**split_name_value(char *arg);
int			size_before_equal(char *string);
int			ft_isspace(int c);
void		lst_cmd_add_back(t_cmd **table_cmd, t_cmd *new);
t_cmd		*create_cmd_node(void);
void		lst_file_add_front(t_files **file_table, t_files *new);
char		*expand_str(char *str);
char		*expand_line(char *word);
char		**expand(char **args);
void		remove_quotes(char *str);
void		init_counter(t_counter *counter);
int			is_quoted(char *delimiter);
void		extract_var(char **line, char **string, int *i, int *k);
void		signal_heredoc_handler(void);
void		signal_handler(void);
int			sig_event(void);
void		sigint_handler_heredoc(int signum);
void		sigint_handler(int signum);
void		set_ignore_signals(void);
int			create_heredoc(t_files *file);
void		set_cmd_signals(void);
void		sigquit_handler(int signum);
void		unlink_all(t_cmd *cmd);
void		handler_create_h_files(t_cmd *cmd);
int			handler_wait_and_signal(int pid);
int			if_is_last_heredoc(t_files *lst);
int			get_heredoc(t_files	*file, t_cmd *current,
				char *input);
void		close_both(int fd, int fd2);
int			handler_eof_h(char *input);
void		routine_heredoc(t_files	*file_list,
				t_cmd	*current, char *input);
int			open_file_no_cmd(t_cmd *cmd);
int			ft_create_pipe(t_cmd *cmd);
char		**env_to_2d_array(t_env *env);
void		remove_variable(char *variable);
char		**env_to_2d_array(t_env *env);
void		remove_variable(char *variable);
void		add_env_variable(char *key, char *value);
int			ft_setenv(char *key, char *value);
bool		is_in_env(char *key);
void		add_back_env(t_env **env, t_env *to_add);
void		change_value_env(char *key, char *value);
void		routine_cmd(t_cmd *current);
void		handler_eof(void);

/* lexer */
typedef struct s_store
{
	char			*input;
	t_token			*tokens;
	t_cmd			*cmds;
	pid_t			pid;
}					t_store;

int			ft_lexer(t_store *store);
int			ft_init_lexer(char *input, t_token *token);
int			ft_check_input(char *input);
int			ft_init_tokens(t_token **token_list, char *input, int *i);
int			ft_error_handler_syntax(char *str, int error, int code);
int			ft_get_type(char *token);

/* lexer utils  */
int			ft_quotes_verif(t_token **token_list, char *input, int *i);
t_token		*ft_new_token(char *value, int type);
void		ft_add_token(t_token **token_list, char *value, int type);
void		ft_token_word(t_token **token, char *input, int *index);
int			ft_syntax_redirection(t_token **token);
int			ft_syntax_pipe(t_token **token);
void		ft_free_token(t_token *token);
void		ft_reset_tokens(t_token **token);
char		*ft_check_pipe(t_token **token_list, char *input, int *i);
int			ft_token_quotes(t_token **token_list, char *input,
				int *index, char quote);

# define ERR_MSG_SYNTAX "minishell: syntax error near unexpected token"

/* parser + utils */
int			ft_is_redirection_token(t_type type);
int			ft_is_word_token(t_type type);
int			ft_is_heredoc(t_token *token);

/* expander */
void		ft_expander(t_store *store, t_token **tokens_list);

void		ft_variables_expansion(t_store *store, t_token *token,
				int *index);
char		*ft_escape_dollar(t_token *token, int *index);
int			ft_check_escape(char *str, int index);
char		*ft_check_variable(t_store *store, char *input);
char		*ft_process_var(t_store *data, char *res, int *i);
char		*ft_process_var_error(char *res, int *i);
char		*ft_process_digit_escape(char *res, int *i);
char		*ft_replace_var(t_store *data, char *res, int *i);
char		*ft_replace_var_error(char *res, int *i);
int			len_to_next_char(char *str, int i, char c);
char		*dquote_expand(char *to_expand, int *start);
char		*quote_expand(char *str, int *start);
char		*normal_expand(char *to_expand, int *start);
char		**split_expand(char *to_split);
void		add_until_dollard(char **dest, char *str, int *i);
char		*extract_variable(char *str, int *start);

/* parser */
int			ft_parser(t_store *data, t_token *token_list);
t_cmd		*ft_init_tree(t_token **token_list, t_store *data);
void		add_args_default(t_cmd *node);
void		ft_add_args_default(t_cmd *node);
int			ambiguous_redirect(char *msg);
int			error_parsing(char *msg);

t_cmd		*ft_handle_cmd(t_token **save,
				t_cmd **last, int *first, t_store *data);
void		ft_add_args(t_token **save, t_cmd *cmd);
void		ft_handle_pipe(t_token **save, t_cmd **current, int *first);
void		ft_add_redirect(t_token **save, t_cmd **current, t_store *data);
void		ft_join_cmd(t_token **save);
t_cmd		*ft_parser_cmd(t_token *token, t_cmd *last);
t_cmd		*ft_create_node(char *value);
int			ft_is_builtin(char *s);
char		*ft_define_path(char *cmd);
void		ft_check_if_exists(t_cmd *node);
void		ft_free_pointer(char *ptr);
t_cmd		*ft_parser_first_redir(t_token *token, t_cmd *last, t_store *data);
int			ft_error_syntax(char *s, int error, bool code);
void		ft_fill_args(t_token **save, t_cmd *cmd, int count);
void		ft_create_redirect(t_cmd *cmd);
int			ft_parse_input(t_cmd **cmd, t_token **token);
int			ft_parse_append(t_cmd **cmd, t_token **token);
int			ft_parse_trunc(t_cmd **cmd, t_token **token);
int			ft_parse_heredoc(t_store *data, t_cmd **cmd, t_token **token);

int			ft_reset_redirect(t_files *redir, bool infile);
int			ft_open_file_trunc(t_files *trunc, char *filename);
int			ft_open_file_append(t_files *append, char *filename);
int			ft_open_input(t_files *input, char *filename);
void		ft_cmd_error(t_cmd *node, int i);
char		*ft_find_path(char **env, char *cmd);
int			ft_expander_heredoc(t_store *data, char *input);
int			ft_error_handler(char *cmd, char *detail,
				char *errmsg, int errcode);
t_cmd		*ft_parser_input(char *input);

typedef enum e_free_arg
{
	FREE_DEST,
	FREE_SRC
}					t_free_arg;

#endif
