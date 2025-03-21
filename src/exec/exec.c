/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:55:46 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/21 21:36:18 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	validate_access(const char *path, t_command *node,
	t_shell *shell, char **argv)
{
	if (path == NULL)
	{
		free_argv(argv);
		err_exit(node, "command not found", 127, shell);
	}
	if (access(path, F_OK) < 0)
	{
		free_argv(argv);
		err_exit(node, "command not found", 127, shell);
	}
}

void	validate_access_02(const char *path, t_command *node,
	t_shell *shell, char **argv)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		free_argv(argv);
		perror("stat error");
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(st.st_mode))
	{
		free_argv(argv);
		err_exit(node, "Is a directory", 126, shell);
	}
	if (access(path, X_OK) < 0)
	{
		free_argv(argv);
		err_exit(node, "Permission denied", 126, shell);
	}
}

int	exec_nonbuiltin(t_command *node, t_shell *shell)
{
	char	*path;
	char	**argv;
	char	**env;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	path = argv[0];
	if (ft_strchr(path, '/') == NULL)
		path = search_path(path, shell);
	validate_access(path, node, shell, argv);
	validate_access_02(path, node, shell, argv);
	env = get_environ(shell->envmap);
	execve(path, argv, env);
	free(path);
	free(argv);
	free_argv(env);
	reset_redirect(node->command->redirects);
	fatal_error("execve");
}

static pid_t	exec_pipeline(t_command *current, t_shell *shell, t_command *node)
{
	pid_t		pid;

	if (!current)
		return (-1);
	prepare_pipe(current);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		reset_signal();
		if (open_redirect_file(current, shell) < 0)
			exit(EXIT_FAILURE);
		prepare_pipe_child(current);
		if (is_builtin(current))
			exit(exec_builtin(current, shell, node));
		else
			exec_nonbuiltin(current, shell);
	}
	prepare_pipe_parent(current);
	if (current->next)
		return (exec_pipeline(current->next, shell, node));
	return (pid);
}

int	exec(t_command *node, t_shell *shell)
{
	pid_t	last_pid;

	last_pid = exec_pipeline(node, shell, node);
	shell->last_status = wait_pipeline(last_pid);
	return (shell->last_status);
}
