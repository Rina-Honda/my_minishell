/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:56:04 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 16:10:54 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize_error(const char *location, char **rest,
		char *line, t_shell *shell)
{
	shell->syntax_error = true;
	perror_prefix();
	ft_dprintf(STDERR_FILENO,
		"syntax error near unexpected character `%c\n in %s\n",
		*line, location);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest,
		t_token *token, t_shell *shell)
{
	shell->syntax_error = true;
	perror_prefix();
	ft_dprintf(STDERR_FILENO,
		"syntax error near unexpected token `%s in %s\n",
		token->word, location);
	while (token && !at_eof(token))
		token = token->next;
	*rest = token;
}
