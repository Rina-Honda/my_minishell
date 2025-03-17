/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:29:42 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 23:30:15 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
