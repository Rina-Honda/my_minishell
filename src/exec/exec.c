/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:55:46 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 23:00:34 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	validate_access(const char *path, const char *filename)
{
	struct stat	st;

	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
	if (stat(path, &st) == -1)
	{
		perror("stat error");
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(st.st_mode))
		err_exit(filename, "Is a directory", 126);
	if (access(path, X_OK) < 0)
		err_exit(filename, "Permission denied", 126);
}

int	exec_nonbuiltin(t_command *node)
{
	char	*path;
	char	**argv;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	path = argv[0];
	if (strchr(path, '/') == NULL)
		path = search_path(path);
	validate_access(path, argv[0]);
	execve(path, argv, get_environ(envmap));
	free(argv);
	reset_redirect(node->command->redirects);
	fatal_error("execve");
}

pid_t	exec_pipeline(t_command *node)
{
	pid_t		pid;

	if (!node)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		reset_signal();
		if (open_redirect_file(node) < 0)
			exit(EXIT_FAILURE); //todo
		prepare_pipe_child(node);
		if (is_builtin(node))
			exit(exec_builtin(node));
		else
			exec_nonbuiltin(node);
	}
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next));
	return (pid);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	setup_sigint_newline();
	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			if (WIFSIGNALED(wstatus))
				status = 128 + WTERMSIG(wstatus);
			else
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	setup_sigint_with_signum();
	return (status);
}

int	exec(t_command *node)
{
	pid_t	last_pid;
	int		status;

	if (!node->next && is_builtin(node))
	{
		if (open_redirect_file(node) < 0)
			exit(EXIT_FAILURE); //todo
		status = exec_builtin(node);
	}
	else
	{
		last_pid = exec_pipeline(node);
		status = wait_pipeline(last_pid);
	}
	return (status);
}
