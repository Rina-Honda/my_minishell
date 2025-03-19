/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:13:14 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 17:00:47 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_word(const char *s)
{
	return (*s && !is_metachar(*s));
}

static bool	consume_single_quote(char **rest, char *line, t_shell *shell)
{
	if (*line == SINGLE_QUOTE)
	{
		line++;
		while (*line && *line != SINGLE_QUOTE)
			line++;
		if (*line == '\0')
			tokenize_error("Unclosed single quote", &line, line, shell);
		else
			line++;
		*rest = line;
		return (true);
	}
	return (false);
}

static bool	consume_double_quote(char **rest, char *line, t_shell *shell)
{
	if (*line == DOUBLE_QUOTE)
	{
		line++;
		while (*line && *line != DOUBLE_QUOTE)
			line++;
		if (*line == '\0')
			tokenize_error("Unclosed double quote", &line, line, shell);
		else
			line++;
		*rest = line;
		return (true);
	}
	return (false);
}

t_token	*word(char **rest, char *line, t_shell *shell)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metachar(*line))
	{
		if (consume_single_quote(&line, line, shell))
			;
		else if (consume_double_quote(&line, line, shell))
			;
		else
			line++;
	}
	word = ft_strndup(start, line - start);
	if (word == NULL)
		fatal_error("ft_strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}
