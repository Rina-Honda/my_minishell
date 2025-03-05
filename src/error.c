/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:16:59 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/05 23:29:58 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_error = false;

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

void	err_exit(const char *location, const char *msg, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, msg);
	exit(status);
}

void	assert_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void	todo(const char *msg)
{
	dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}

void	tokenize_error(const char *location, char **rest, char *line)
{
	syntax_error = true;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	// lineを最後まで読んで、呼び出し元のtokenizeでwhileループを抜ける
	// →exitしない代わり
	while (*line)
		line++;
	*rest = line;
}
