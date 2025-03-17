/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:53:20 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:08:07 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_metachar(char c)
{
	if (is_blank(c))
		return (true);
	return (c && ft_strchr("|&;()<> \t\n", c));
}

bool	is_metachar_notblank(char c)
{
	return (c && ft_strchr("|&;()<>", c));
}

bool	at_eof(t_token *token)
{
	return (token->kind == TK_EOF);
}

bool	starts_with(const char *s, const char *keyword)
{
	return (ft_memcmp(s, keyword, ft_strlen(keyword)) == 0);
}

bool	is_alpha_underscore(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_underscore(char c)
{
	return (is_alpha_underscore(c) || ft_isdigit(c));
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}
