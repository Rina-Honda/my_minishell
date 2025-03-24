/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:44:22 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/25 08:34:28 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_loop(int pipefd[2], const char *delimiter, t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (readline_sigint(shell, line))
		{
			free_node(shell->node_head);
			free_map(shell->envmap);
			exit(130);
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

int	read_heredoc(const char *delimiter, t_shell *shell)
{
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		fatal_error("pipe");
	shell->readline_interrupted = false;
	heredoc_loop(pipefd, delimiter, shell);
	close(pipefd[1]);
	if (shell->readline_interrupted)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}
