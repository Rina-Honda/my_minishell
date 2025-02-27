/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:30:51 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/28 00:55:59 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// __attribute__((noreturn))はコンパイラにreturnしないことを伝える
void	fatal_error(const char *msg) __attribute__((noreturn));

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

int	interpret(char *line)
{
	// 環境変数グローバルで使える
	extern char	**environ;
	char		*argv[] = {line, NULL};
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	// child process
	if (pid == 0)
	{
		// execve: pathnameをもとにファイル実行
		execve(line, argv, environ);
		fatal_error("execve");
	}
	// parent process
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		// lineが空の場合はadd_historyしない仕様
		if (*line)
		{
			add_history(line);
			interpret(line);
		}
		free(line);
	}
	exit(0);
}
