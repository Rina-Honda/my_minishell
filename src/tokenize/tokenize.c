/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:18:07 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:13:38 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
