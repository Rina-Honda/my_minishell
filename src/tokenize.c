/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:18:07 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 00:06:20 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		fatal_error("ft_calloc");
	token->word = word;
	token->kind = kind;
	return (token);
}

bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
}

t_token	*operator(char **rest, char *line)
{
	static char *const	operators[] = {">>", "<<", "||", "&&", ";;", ">", "<", "&", ";", "(", ")", "|", "\n"};
	size_t	i = 0;
	char	*operator;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (starts_with(line, operators[i]))
		{
			operator = ft_strdup(operators[i]);
			if (!operator)
				fatal_error("ft_strdup");
			*rest = line + ft_strlen(operator);
			return (new_token(operator, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
}

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

t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*token;

	syntax_error = false;
	head.next = NULL;
	token = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_metachar(*line))
		{
			token->next = operator(&line, line);
			token = token->next;
		}
		else if (is_word(line))
		{
			token->next = word(&line, line);
			token = token->next;
		}
		else
			tokenize_error("Unexpected Token", &line, line);
	}
	token->next = new_token(NULL, TK_EOF);
	return (head.next);
}

char	**tail_recursive(t_token *token, int count, char **argv)
{
	if (token == NULL || token->kind == TK_EOF)
		return (argv);
	argv = realloc(argv, (count + 2) * sizeof(char *));
	argv[count] = ft_strdup(token->word);
	if (argv[count] == NULL)
		fatal_error("ft_strdup");
	argv[count + 1] = NULL;
	return (tail_recursive(token->next, count + 1, argv));
}

char	**token_list_to_argv(t_token *token)
{
	char	**argv;

	argv = ft_calloc(1, sizeof(char *));
	if (argv == NULL)
		fatal_error("ft_calloc");
	return (tail_recursive(token, 0, argv));
}
