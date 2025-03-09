/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:18:57 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/09 13:13:29 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(t_command_kind kind)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(*command));
	if (!command)
		fatal_error("ft_calloc");
	command->kind = kind;
	return (command);
}

void	append_token_recursive(t_token **tokens, t_token *token)
{
	if (*tokens == NULL)
	{
		*tokens = token;
		return ;
	}
	append_token_recursive(&(*tokens)->next, token);
}

t_token	*tokendup(t_token *token)
{
	char	*word;

	word = ft_strdup(token->word);
	if (!word)
		fatal_error("ft_strdup");
	return (new_token(word, token->kind));
}

bool	equal_operator(t_token *token, char *operator)
{
	if (token->kind != TK_OP)
		return (false);
	return (strcmp(token->word, operator) == 0);
}

void	append_command_recursive(t_command **command, t_command *element)
{
	if (!(*command))
	{
		*command = element;
		return ;
	}
	// すでにredirectが入っていたら、末尾に追記
	append_command_recursive(&(*command)->next, element);
}

t_command	*redirect_out(t_token **rest, t_token *token)
{
	t_command	*command;

	command = new_command(REDIR_OUT);
	command->filename = tokendup(token->next);
	command->targetfd = STDOUT_FILENO;
	*rest = token->next->next;
	return (command);
}

t_command	*redirect_in(t_token **rest, t_token *token)
{
	t_command	*command;

	command = new_command(REDIR_IN);
	command->filename = tokendup(token->next);
	command->targetfd = STDIN_FILENO;
	*rest = token->next->next;
	return (command);
}

t_command	*redirect_append(t_token **rest, t_token *token)
{
	t_command	*command;

	command = new_command(REDIR_APPEND);
	command->filename = tokendup(token->next);
	command->targetfd = STDOUT_FILENO;
	*rest = token->next->next;
	return (command);
}

t_command	*redirect_heredoc(t_token **rest, t_token *token)
{
	t_command	*command;

	command = new_command(REDIR_HEREDOC);
	command->delimiter = tokendup(token->next);
	command->targetfd = STDIN_FILENO;
	*rest = token->next->next;
	return (command);
}

void	append_command_element(t_command *command, t_token **rest, t_token *token)
{
	if (token->kind == TK_WORD)
	{
		append_token_recursive(&command->args, tokendup(token));
		token = token->next;
	}
	else if (equal_operator(token, ">") && token->next->kind == TK_WORD)
		append_command_recursive(&command->redirects, redirect_out(&token, token));
	else if (equal_operator(token, "<") && token->next->kind == TK_WORD)
		append_command_recursive(&command->redirects, redirect_in(&token, token));
	else if (equal_operator(token, ">>") && token->next->kind == TK_WORD)
		append_command_recursive(&command->redirects, redirect_append(&token, token));
	else if (equal_operator(token, "<<") && token->next->kind == TK_WORD)
		append_command_recursive(&command->redirects, redirect_heredoc(&token, token));
	else
		todo("append_command_element");
	// 読んだ分更新
	*rest = token;
}

t_command	*parse(t_token *token)
{
	t_command	*command;

	command = new_command(SIMPLE_CMD);
	append_command_element(command, &token, token);
	while (token && !at_eof(token))
		append_command_element(command, &token, token);
	return (command);
}
