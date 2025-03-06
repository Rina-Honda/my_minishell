/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:18:57 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/07 01:06:17 by rhonda           ###   ########.fr       */
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

bool	at_eof(t_token *token)
{
	return (token->kind == TK_EOF);
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

t_command	*parse(t_token *token)
{
	t_command	*command;

	command = new_command(SIMPLE_CMD);
	while (token && !at_eof(token))
	{
		//!? わからん→今はまだcommandひとつに全てのtokenを引数として詰めてる
		if (token->kind == TK_WORD)
		{
			append_token_recursive(&command->args, tokendup(token));
			token = token->next;
		}
		//? 初手はワードがくる想定だから？
		else
			parse_error("Unexpected Token", &token, token);
	}
	return (command);
}
