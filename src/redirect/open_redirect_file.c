/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirect_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:43:22 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 11:54:23 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	openfd(t_command *node)
{
	if (node->kind == REDIR_OUT)
		return (open(node->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (node->kind == REDIR_IN)
		return (open(node->filename->word, O_RDONLY));
	else if (node->kind == REDIR_APPEND)
		return (open(node->filename->word,
			O_CREAT | O_WRONLY | O_APPEND, 0644));
	else if (node->kind == REDIR_HEREDOC)
		return (read_heredoc(node->delimiter->word));
	else
		assert_error("open_redirect_file");
}

int	open_redirect_file(t_command *node)
{
	if (!node)
		return (0);
	if (node->kind == PIPELINE)
	{
		if (open_redirect_file(node->command) < 0)
			return (-1);
		if (open_redirect_file(node->next) < 0)
			return (-1);
		return (0);
	}
	else if (node->kind == SIMPLE_CMD)
		return (open_redirect_file(node->redirects));
	node->filefd = openfd(node);
	if (node->filefd < 0)
	{
		if (node->kind == REDIR_OUT || node->kind == REDIR_IN
			|| node->kind == REDIR_APPEND)
			xperror(node->filename->word);
		return (-1);
	}
	node->filefd = stashfd(node->filefd);
	return (open_redirect_file(node->next));
}
