/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:53:20 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/09 01:23:51 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
DEFINITIONS
       The following definitions are used throughout the rest of this document.
       blank  A space or tab.
       word   A sequence of characters considered as a single unit by the shell.  Also known as a token.
       name   A word consisting only of alphanumeric characters and underscores, and beginning with an alphabetic
              character or an underscore.  Also referred to as an identifier.
       metacharacter
              A character that, when unquoted, separates words.  One of the following:
              |  & ; ( ) < > space tab
       control operator
              A token that performs a control function.  It is one of the following symbols:
              || & && ; ;; ( ) | <newline>
*/

bool	is_blank(char c)
{
	//? 改行もブランク扱い？
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_metachar(char c)
{
	//? blankもメタ文字？→そう
	if (is_blank(c))
		return (true);
	return (c && ft_strchr("|&;()<> \t\n", c));
}

bool	at_eof(t_token *token)
{
	return (token->kind == TK_EOF);
}

bool	starts_with(const char *s, const char *keyword)
{
	return (ft_memcmp(s, keyword, ft_strlen(keyword)) == 0);
}
