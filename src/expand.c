/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:10:47 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/06 01:07:48 by rhonda           ###   ########.fr       */
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
	new_word = NULL;
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

void	expand_quote_removal_recursive(t_command *command)
{
	if (!command)
		return ;
	remove_quote_recursive(command->args);
	expand_quote_removal_recursive(command->next);
}

void	expand(t_command *command)
{
	expand_quote_removal_recursive(command);
}
