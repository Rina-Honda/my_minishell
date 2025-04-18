/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:32:21 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/24 22:51:53 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_redirect_recursive(t_command **redirect, t_command *element)
{
	if (!(*redirect))
	{
		*redirect = element;
		return ;
	}
	append_redirect_recursive(&(*redirect)->next, element);
}

void	append_command_elem(t_command *command, t_token **rest,
		t_token *token, t_shell *shell)
{
	if (token->kind == TK_WORD)
	{
		append_token_recursive(&command->args, tokendup(token));
		token = token->next;
	}
	else if (equal_operator(token, ">") && token->next->kind == TK_WORD)
		append_redirect_recursive(&command->redirects,
			redirect_out(&token, token));
	else if (equal_operator(token, "<") && token->next->kind == TK_WORD)
		append_redirect_recursive(&command->redirects,
			redirect_in(&token, token));
	else if (equal_operator(token, ">>") && token->next->kind == TK_WORD)
		append_redirect_recursive(&command->redirects,
			redirect_append(&token, token));
	else if (equal_operator(token, "<<") && token->next->kind == TK_WORD)
		append_redirect_recursive(&command->redirects,
			redirect_heredoc(&token, token));
	else
		parse_error("append_command_elem", &token, token, shell);
	*rest = token;
}

bool	is_control_operator(t_token *token)
{
	static char *const	operators[] = {"||", "&", "&&",
		";", ";;", "(", ")", "|", "\n"};
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

t_command	*simple_command(t_token **rest, t_token *token, t_shell *shell)
{
	t_command	*command;

	command = new_command(SIMPLE_CMD);
	append_command_elem(command, &token, token, shell);
	while (token && !at_eof(token) && !is_control_operator(token))
		append_command_elem(command, &token, token, shell);
	*rest = token;
	return (command);
}
