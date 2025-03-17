/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:10:47 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 23:12:38 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
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

void	append_single_quote(char **dst, char **rest, char *ptr)
{
	if (*ptr == SINGLE_QUOTE)
	{
		append_char(dst, *ptr);
		ptr++;
		while (*ptr != SINGLE_QUOTE)
		{
			if (*ptr == '\0')
				assert_error("Unclosed single quote");
			append_char(dst, *ptr);
			ptr++;
		}
		append_char(dst, *ptr);
		ptr++;
		*rest = ptr;
	}
	else
		assert_error("Expected single quote");
}

void	append_double_quote(char **dst, char **rest, char *ptr)
{
	if (*ptr == DOUBLE_QUOTE)
	{
		append_char(dst, *ptr);
		ptr++;
		while (*ptr != DOUBLE_QUOTE)
		{
			if (*ptr == '\0')
				assert_error("Unclosed double quote");
			else if (is_variable(ptr))
				expand_variable_str(dst, &ptr, ptr);
			else if (is_special_parameter(ptr))
				expand_special_parameter_str(dst, &ptr, ptr);
			else
			{
				append_char(dst, *ptr);
				ptr++;
			}
		}
		append_char(dst, *ptr);
		ptr++;
		*rest = ptr;
	}
	else
		assert_error("Expected double quote");
}

void	expand_variable_token_recursive(t_token *token)
{
	char	*new_word;
	char	*ptr;

	if (!token || token->kind != TK_WORD || !token->word)
		return ;
	ptr = token->word;
	new_word = ft_calloc(1, sizeof(char));
	if (!new_word)
		fatal_error("ft_calloc");
	while (*ptr && !is_metachar_notblank(*ptr))
	{
		if (*ptr == SINGLE_QUOTE)
			append_single_quote(&new_word, &ptr, ptr);
		else if (*ptr == DOUBLE_QUOTE)
			append_double_quote(&new_word, &ptr, ptr);
		else if (is_variable(ptr))
			expand_variable_str(&new_word, &ptr, ptr);
		else if (is_special_parameter(ptr))
			expand_special_parameter_str(&new_word, &ptr, ptr);
		else
		{
			append_char(&new_word, *ptr);
			ptr++;
		}
	}
	free(token->word);
	token->word = new_word;
	expand_variable_token_recursive(token->next);
}

void	expand_variable_recursive(t_command *node)
{
	if (!node)
		return ;
	expand_variable_token_recursive(node->args);
	expand_variable_token_recursive(node->filename);
	expand_variable_recursive(node->redirects);
	expand_variable_recursive(node->command);
	expand_variable_recursive(node->next);
}

void	expand(t_command *node)
{
	expand_variable_recursive(node);
	expand_quote_removal_recursive(node);
}
