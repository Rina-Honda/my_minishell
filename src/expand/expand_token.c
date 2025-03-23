/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:10:47 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/23 21:46:14 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	append_double_quote(char **dst, char **rest, char *ptr, t_shell *shell)
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
				expand_variable_str(dst, &ptr, ptr, shell);
			else if (is_special_parameter(ptr))
				expand_special_parameter_str(dst, &ptr, ptr, shell);
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

void	expand_variable_token_recursive(t_token *token, t_shell *shell)
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
			append_double_quote(&new_word, &ptr, ptr, shell);
		else if (is_variable(ptr))
			expand_variable_str(&new_word, &ptr, ptr, shell);
		else if (is_special_parameter(ptr))
			expand_special_parameter_str(&new_word, &ptr, ptr, shell);
		else
			append_char(&new_word, *ptr++);
	}
	free(token->word);
	token->word = new_word;
	expand_variable_token_recursive(token->next, shell);
}

void	expand_variable_recursive(t_command *node, t_shell *shell)
{
	if (!node)
		return ;
	expand_variable_token_recursive(node->args, shell);
	expand_variable_token_recursive(node->filename, shell);
	expand_variable_recursive(node->redirects, shell);
	expand_variable_recursive(node->command, shell);
	expand_variable_recursive(node->next, shell);
}
