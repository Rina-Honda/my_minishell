/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:28:52 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:09:08 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	readline_interrupted = false;

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		fatal_error("pipe");
	readline_interrupted = false;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (readline_interrupted)
		{
			free(line);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		dprintf(pipefd[1], "%s\n", line);
		free(line);
	}
	close(pipefd[1]);
	if (readline_interrupted)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
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
	else if (node->kind == REDIR_OUT)
		node->filefd = open(node->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->kind == REDIR_IN)
		node->filefd = open(node->filename->word, O_RDONLY);
	else if (node->kind == REDIR_APPEND)
		node->filefd = open(node->filename->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->kind == REDIR_HEREDOC)
		node->filefd = read_heredoc(node->delimiter->word);
	else
		assert_error("open_redirect_file");
	if (node->filefd < 0)
	{
		if (node->kind == REDIR_OUT || node->kind == REDIR_IN || node->kind == REDIR_APPEND)
			xperror(node->filename->word);
		return (-1);
	}
	node->filefd = stashfd(node->filefd);
	return (open_redirect_file(node->next));
}

bool	is_redirect(t_command *command)
{
	if (command->kind == REDIR_OUT)
		return (true);
	if (command->kind == REDIR_IN)
		return (true);
	if (command->kind == REDIR_APPEND)
		return (true);
	if (command->kind == REDIR_HEREDOC)
		return (true);
	return (false);
}

void	do_redirect(t_command *redirect)
{
	if (!redirect)
		return ;
	if (is_redirect(redirect))
	{
		redirect->stashed_targetfd = stashfd(redirect->targetfd);
		dup2(redirect->filefd, redirect->targetfd);
	}
	else
		assert_error("do_redirect");
	do_redirect(redirect->next);
}

void	reset_redirect(t_command *redirect)
{
	if (!redirect)
		return ;
	reset_redirect(redirect->next);
	if (is_redirect(redirect))
	{
		close(redirect->filefd);
		close(redirect->targetfd);
		dup2(redirect->stashed_targetfd, redirect->targetfd);
	}
	else
		assert_error("reset_redirect");
}
