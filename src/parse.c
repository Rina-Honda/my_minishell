/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:18:57 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/16 23:57:17 by rhonda           ###   ########.fr       */
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
	return (ft_strcmp(token->word, operator) == 0);
}

void	append_redirect_recursive(t_command **redirect, t_command *element)
{
	if (!(*redirect))
	{
		*redirect = element;
		return ;
	}
	append_redirect_recursive(&(*redirect)->next, element);
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
		append_redirect_recursive(&command->redirects, redirect_out(&token, token));
	else if (equal_operator(token, "<") && token->next->kind == TK_WORD)
		append_redirect_recursive(&command->redirects, redirect_in(&token, token));
	else if (equal_operator(token, ">>") && token->next->kind == TK_WORD)
		append_redirect_recursive(&command->redirects, redirect_append(&token, token));
	else if (equal_operator(token, "<<") && token->next->kind == TK_WORD)
		append_redirect_recursive(&command->redirects, redirect_heredoc(&token, token));
	else
		todo("append_command_element");
	*rest = token;
}

bool	is_control_operator(t_token *token)
{
	static char *const	operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(operators[i]))
	{
		if (starts_with(token->word, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

t_command	*simple_command(t_token **rest, t_token *token)
{
	t_command	*command;

	command = new_command(SIMPLE_CMD);
	append_command_element(command, &token, token);
	while (token && !at_eof(token) && !is_control_operator(token))
		append_command_element(command, &token, token);
	*rest = token;
	return (command);
}

t_command	*pipeline(t_token **rest, t_token *token)
{
	t_command	*node;

	node = new_command(PIPELINE);
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->command = simple_command(&token, token);
	if (equal_operator(token, "|"))
		node->next = pipeline(&token, token->next);
	*rest = token;
	return (node);
}

t_command	*parse(t_token *token)
{
	return (pipeline(&token, token));
}
