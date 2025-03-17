/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:32:21 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:14:35 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

//include
# include "../libfts/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>

//define
# define PATH_MAX 4096
# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

//typedef
typedef enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
}	t_token_kind;

typedef struct s_token
{
	char			*word;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

typedef enum e_command_kind
{
	PIPELINE,
	SIMPLE_CMD,
	REDIR_OUT,
	REDIR_IN,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_command_kind;

typedef struct s_command
{
	t_command_kind		kind;
	struct s_command	*next;
	// comamnd
	t_token				*args;
	struct s_command	*redirects;
	// redirect
	int					targetfd;
	t_token				*filename;
	t_token				*delimiter;
	int					filefd;
	int					stashed_targetfd;
	// pipeline
	int					inpipe[2];
	int					outpipe[2];
	struct s_command	*command;
}	t_command;

typedef struct s_item
{
	char			*name;
	char			*value;
	struct s_item	*next;
}	t_item;

typedef struct s_map
{
	t_item	item_head;
}	t_map;

// global variable
extern bool						syntax_error;
extern int						last_status;
extern bool						readline_interrupted;
extern volatile sig_atomic_t	sig;
extern t_map					*envmap;

//prottype
// tokenize
t_token	*tokenize(char *line);
char	**token_list_to_argv(t_token *token);
t_token	*new_token(char *word, t_token_kind kind);
bool	is_blank(char c);
bool	consume_blank(char **rest, char *line);
bool	is_metachar(char c);
bool	is_metachar_notblank(char c);
bool	is_alpha_underscore(char c);
bool	is_alpha_num_underscore(char c);
bool	is_identifier(const char *s);
t_token	*operator(char **rest, char *line);
t_token	*new_token(char *word, t_token_kind kind);
t_token	*tokendup(t_token *token);
void	append_token_recursive(t_token **tokens, t_token *token);
bool	at_eof(t_token *token);
bool	equal_operator(t_token *token, char *operator);
bool	is_word(const char *s);
t_token	*word(char **rest, char *line);

// parse
t_command	*parse(t_token *token);
t_command	*new_command(t_command_kind kind);
t_command	*pipeline(t_token **rest, t_token *token);
t_command	*redirect_out(t_token **rest, t_token *token);
t_command	*redirect_in(t_token **rest, t_token *token);
t_command	*redirect_append(t_token **rest, t_token *token);
t_command	*redirect_heredoc(t_token **rest, t_token *token);
t_command	*simple_command(t_token **rest, t_token *token);

// expand
void	expand(t_command *node);
void	expand_quote_removal_recursive(t_command *node);
void	append_char(char **s, char c);
bool	is_variable(char *s);
void	expand_variable_str(char **dst, char **rest, char *ptr);
bool	is_special_parameter(char *s);
void	expand_special_parameter_str(char **dst, char **rest, char *ptr);

// exec
int		exec(t_command *node);
int		exec_nonbuiltin(t_command *node)__attribute__((noreturn));
char	*search_path(const char *filename);

// redirect
int		open_redirect_file(t_command *redirect);
void	do_redirect(t_command *redirect);
void	reset_redirect(t_command *redirect);
int		open_redirect_file(t_command *node);
int		stashfd(int fd);
int		read_heredoc(const char *delimiter);

// pipe
void	prepare_pipe(t_command *node);
void	prepare_pipe_child(t_command *node);
void	prepare_pipe_parent(t_command *node);

// signal
void	setup_signal(void);
void	setup_sigint_with_signum(void);
void	handler_signum(int signum);
void	setup_sigint_newline(void);
void	handler_newline(int signum);
void	ignore_sig(int signum);
void	reset_signal(void);
void	reset_sig(int signum);

// env
void	init_env(void);
char	*ft_getenv(const char *name);
char	**get_environ(t_map *map);

// map
t_map	*map_new(void);
int		map_put(t_map *map, const char *str, bool allow_empty_value);
char	*map_get(t_map *map, const char *name);
size_t	map_len(t_map *map, bool count_null_value);
char	*item_get_string(t_item *item);
t_item	*item_new(char *name, char *value);
int		map_unset(t_map *map, const char *name);
int		map_set(t_map *map, const char *name, const char *value);

// builtin
bool	is_builtin(t_command *node);
int		exec_builtin(t_command *node);
int		builtin_exit(char **argv);
int		builtin_export(char **argv);
int		builtin_unset(char **argv);
int		builtin_env(char **argv);
int		builtin_cd(char **argv);
int		builtin_echo(char **argv);
int		builtin_pwd(char **argv);

// error
void	fatal_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *locatino, const char *msg, int status)__attribute__((noreturn));
void	assert_error(const char *msg)__attribute__((noreturn));
void	todo(const char *msg)__attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);
void	parse_error(const char *location, t_token **rest, t_token *token);
void	xperror(const char *location);
void	builtin_error(const char *func, const char *name, const char *err);
void	perror_prefix(void);

// free
void	free_argv(char **argv);
void	free_token(t_token *token);
void	free_node(t_command *node);

// util
bool	starts_with(const char *s, const char *keyword);
int		ft_isspace(char c);
long	ft_strtol(const char *str, char **endptr, int base);
int		ft_strcmp(const char *s1, const char *s2);

#endif