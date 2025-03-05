/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:32:21 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/06 01:02:44 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//include
# include "../libfts/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

//define
# define PATH_MAX 4096
# define ERROR_TOKENIZE 258

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

// global variable
extern bool	syntax_error;

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
	SIMPLE_CMD,
}	t_command_kind;

typedef struct s_command
{
	t_token				*args;
	t_command_kind		kind;
	struct s_command	*next;
}	t_command;

//prottype
// tokenize
t_token	*tokenize(char *line);
char	**token_list_to_argv(t_token *token);
t_token	*new_token(char *word, t_token_kind kind);

// parse
t_command	*parse(t_token *token);

// expand
void	expand(t_command *command);

// error
// __attribute__((noreturn))はコンパイラにreturnしないことを伝える
void	fatal_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *locatino, const char *msg, int status)__attribute__((noreturn));
void	assert_error(const char *msg)__attribute__((noreturn));
void	todo(const char *msg)__attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);

// free
void	free_argv(char **argv);
void	free_token(t_token *token);
void	free_command(t_command *command);

// util
bool	is_metachar(char c);

#endif