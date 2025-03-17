/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:06:20 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:11:39 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		fatal_error("ft_calloc");
	token->word = word;
	token->kind = kind;
	return (token);
}

t_token	*tokendup(t_token *token)
{
	char	*word;

	word = ft_strdup(token->word);
	if (!word)
		fatal_error("ft_strdup");
	return (new_token(word, token->kind));
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

bool	at_eof(t_token *token)
{
	return (token->kind == TK_EOF);
}

bool	equal_operator(t_token *token, char *operator)
{
	if (token->kind != TK_OP)
		return (false);
	return (ft_strcmp(token->word, operator) == 0);
}
