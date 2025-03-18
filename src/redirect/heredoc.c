/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:44:22 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 12:38:25 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	readline_interrupted = false;

static void	heredoc_loop(int pipefd[2], const char *delimiter)
{
	char	*line;

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
		ft_dprintf(pipefd[1], "%s\n", line);
		free(line);
	}
}

int	read_heredoc(const char *delimiter)
{
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		fatal_error("pipe");
	readline_interrupted = false;
	heredoc_loop(pipefd, delimiter);
	close(pipefd[1]);
	if (readline_interrupted)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}
