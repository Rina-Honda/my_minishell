/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:10:47 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/13 23:21:54 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	remove_single_quote(char **dst, char **rest, char *ptr)
{
	if (*ptr == SINGLE_QUOTE)
	{
		// skipe quote
		ptr++;
		while (*ptr != SINGLE_QUOTE)
		{
			//parse時にはじいた事象なのでassert_error
			if (*ptr == '\0')
				assert_error("Unclosed single quote");
			append_char(dst, *ptr);
			ptr++;
		}
		// skipe quote
		ptr++;
		//ポインタ更新
		*rest = ptr;
	}
	else
		assert_error("Expected single quote");
}

void	remove_double_quote(char **dst, char **rest, char *ptr)
{
	if (*ptr == DOUBLE_QUOTE)
	{
		//skip quote
		ptr++;
		while (*ptr != DOUBLE_QUOTE)
		{
			//parse時にはじいた事象なのでassert_error
			if (*ptr == '\0')
				assert_error("Unclosed double quote");
			append_char(dst, *ptr);
			ptr++;
		}
		//skip quote
		ptr++;
		//ポインタ更新
		*rest = ptr;
	}
	else
		assert_error("Expected double quote");
}

void	remove_quote_recursive(t_token *token)
{
	char	*new_word;
	char	*ptr;

	//!? なんでTK_WORDじゃないとだめ？→remoove quoteする必要ないから
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
	// tokenはquote処理を行う
	remove_quote_recursive(node->args);
	remove_quote_recursive(node->filename);
	remove_quote_recursive(node->delimiter);
	// nodeは再帰
	expand_quote_removal_recursive(node->redirects);
	expand_quote_removal_recursive(node->command);
	expand_quote_removal_recursive(node->next);
}

bool	is_variable(char *s)
{
	return (s[0] == '$' && is_alpha_underscore(s[1]));
}

void	expand_variable_str(char **dst, char **rest, char *ptr)
{
	char	*name;
	char	*value;

	name = ft_calloc(1, sizeof(char));
	if (!name)
		fatal_error("ft_calloc");
	if (*ptr != '$')
		assert_error("Expected dollar sign");
	ptr++;
	if (!is_alpha_underscore(*ptr))
		assert_error("Variable must starts with alpha or underscore.");
	append_char(&name, *ptr);
	ptr++;
	while (is_alpha_num_underscore(*ptr))
	{
		append_char(&name, *ptr);
		ptr++;
	}
	value = ft_getenv(name);
	free(name);
	if (value)
	{
		while (*value)
		{
			append_char(dst, *value);
			value++;
		}
	}
	*rest = ptr;
}

bool	is_special_parameter(char *s)
{
	return (s[0] == '$' || s[1] == '?');
}

void	append_num(char **dst, unsigned int num)
{
	if (num == 0)
	{
		append_char(dst, '0');
		return ;
	}
	if (num / 10 != 0)
		append_num(dst, num / 10);
	append_char(dst, '0' + (num % 10));
}

void	expand_special_parameter_str(char **dst, char **rest, char *ptr)
{
	if (!is_special_parameter(ptr))
		assert_error("Expand special parameter");
	ptr += 2;
	append_num(dst, last_status);
	*rest = ptr;
}

void	append_single_quote(char **dst, char **rest, char *ptr)
{
	if (*ptr == SINGLE_QUOTE)
	{
		// まだskip quoteしない
		append_char(dst, *ptr);
		ptr++;
		while (*ptr != SINGLE_QUOTE)
		{
			if (*ptr == '\0')
				assert_error("Unclosed single quote");
			append_char(dst, *ptr);
			ptr++;
		}
		// まだskip quoteしない
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
		// まだskip quoteしない
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
		// まだskip quoteしない
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
		else if (is_special_parameter(ptr)) // $? は is_variableに引っかからない
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
