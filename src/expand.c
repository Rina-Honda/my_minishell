/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:10:47 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/04 00:03:24 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += strlen(*s);
	new = malloc(size);
	if (!new)
		fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	quote_removal_recursive(t_token *token)
{
	char	*new_word;
	char	*ptr;

	//!? なんでTK_WORDじゃないとだめ？→remoove quoteする必要ないから
	if (token == NULL || token->kind != TK_WORD || token->word == NULL)
		return ;
	ptr = token->word;
	new_word = NULL;
	while (*ptr && !is_metachar(*ptr))
	{
		if (*ptr == SINGLE_QUOTE)
		{
			// skipe quote
			ptr++;
			while (*ptr != SINGLE_QUOTE)
			{
				if (*ptr == '\0')
					todo("Unclosed single quote");
				append_char(&new_word, *ptr);
				ptr++;
			}
			// skipe quote
			ptr++;
		}
		else
		{
			append_char(&new_word, *ptr);
			ptr++;
		}
	}
	free(token->word);
	token->word = new_word;
	quote_removal_recursive(token->next);
}

void	expand(t_token *token)
{
	quote_removal_recursive(token);
}
