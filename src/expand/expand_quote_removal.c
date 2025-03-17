/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:02:36 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 23:03:35 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_single_quote(char **dst, char **rest, char *ptr)
{
	if (*ptr == SINGLE_QUOTE)
	{
		ptr++;
		while (*ptr != SINGLE_QUOTE)
		{
			if (*ptr == '\0')
				assert_error("Unclosed single quote");
			append_char(dst, *ptr);
			ptr++;
		}
		ptr++;
		*rest = ptr;
	}
	else
		assert_error("Expected single quote");
}

void	remove_double_quote(char **dst, char **rest, char *ptr)
{
	if (*ptr == DOUBLE_QUOTE)
	{
		ptr++;
		while (*ptr != DOUBLE_QUOTE)
		{
			if (*ptr == '\0')
				assert_error("Unclosed double quote");
			append_char(dst, *ptr);
			ptr++;
		}
		ptr++;
		*rest = ptr;
	}
	else
		assert_error("Expected double quote");
}

void	remove_quote_recursive(t_token *token)
{
	char	*new_word;
	char	*ptr;

	if (token == NULL || token->kind != TK_WORD || token->word == NULL)
		return ;
	ptr = token->word;
	new_word = ft_calloc(1, sizeof(char));
	if (!new_word)
		fatal_error("ft_calloc");
	while (*ptr && !is_metachar(*ptr))
	{
		if (*ptr == SINGLE_QUOTE)
			remove_single_quote(&new_word, &ptr, ptr);
		else if (*ptr == DOUBLE_QUOTE)
			remove_double_quote(&new_word, &ptr, ptr);
		else
		{
			append_char(&new_word, *ptr);
			ptr++;
		}
	}
	free(token->word);
	token->word = new_word;
	remove_quote_recursive(token->next);
}

void	expand_quote_removal_recursive(t_command *node)
{
	if (!node)
		return ;
	remove_quote_recursive(node->args);
	remove_quote_recursive(node->filename);
	remove_quote_recursive(node->delimiter);
	expand_quote_removal_recursive(node->redirects);
	expand_quote_removal_recursive(node->command);
	expand_quote_removal_recursive(node->next);
}
