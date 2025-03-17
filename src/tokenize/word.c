/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:13:14 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:13:41 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_word(const char *s)
{
	return (*s && !is_metachar(*s));
}

t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metachar(*line))
	{
		if (*line == SINGLE_QUOTE)
		{
			line++;
			while (*line && *line != SINGLE_QUOTE)
				line++;
			if (*line == '\0')
			{
				tokenize_error("Unclosed single quote", &line, line);
				break ;
			}
			line++;
		}
		else if (*line == DOUBLE_QUOTE)
		{
			line++;
			while (*line && *line != DOUBLE_QUOTE)
				line++;
			if (*line == '\0')
			{
				tokenize_error("Unclosed double quote", &line, line);
				break ;
			}
			line++;
		}
		else
			line++;
	}
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("ft_strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}
