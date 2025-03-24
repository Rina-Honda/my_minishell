/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:55:46 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/25 08:31:00 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	validate_access(const char *path, t_shell *shell, char **argv)
{
	if (path == NULL)
	{
		free_argv(argv);
		cmd_err_exit(127, shell);
	}
	if (access(path, F_OK) < 0)
	{
		free_argv(argv);
		cmd_err_exit(127, shell);
	}
}

void	validate_access_02(const char *path, t_command *node,
	t_shell *shell, char **argv)
{
	struct stat	st;

	if (node->command->args->word[0] == '\0')
	{
		free(argv);
		free_node(node);
		free_map(shell->envmap);
		exit(0);
	}
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
	if (argv[0][0] == '\0')
	{
		free_argv(argv);
		free_node(node);
		free_map(shell->envmap);
		exit(EXIT_FAILURE);
	}
	if (ft_strchr(argv[0], '/') == NULL)
		path = search_path(argv[0], shell);
	else
		path = argv[0];
	validate_access(path, shell, argv);
	validate_access_02(path, node, shell, argv);
	env = get_environ(shell->envmap);
	execve(path, argv, env);
	free(path);
	free_argv(argv);
	free_argv(env);
	reset_redirect(node->command->redirects);
	free_map(shell->envmap);
	free_node(shell->node_head);
	fatal_error("execve");
}

// TODO 関数を分割する
static pid_t	exec_pipeline(t_command *current, t_shell *shell
	, t_command *node)
{
	pid_t		pid;
	int			status;

	if (!current)
		return (-1);
	prepare_pipe(current);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		setup_sigint_with_signum();
		if (open_redirect_file(current, shell) < 0)
		{
			printf("g_sig: %d\n", g_sig);
			
			free_node(shell->node_head);
			free_map(shell->envmap);
			printf("last_status: %d\n", shell->last_status);
			exit(shell->last_status);
		}
		reset_signal();
		prepare_pipe_child(current);
		if (is_builtin(current))
		{
			status = exec_builtin(current, shell, node);
			free_map(shell->envmap);
			free_node(node);
			exit(status);
		}
		else
			exec_nonbuiltin(current, shell);
	}
	prepare_pipe_parent(current);
	if (current->next)
		return (exec_pipeline(current->next, shell, node));
	return (pid);
}

void print_cmd_not_found(t_command *node, t_shell *shell)
{
	char	*path;
	t_command *cur = node;

	while (cur)
	{
		if (cur->command && cur->command->args && !is_builtin(cur))
		{
			char **argv = token_list_to_argv(cur->command->args);
			path = argv[0];
			if (ft_strchr(path, '/') == NULL)
				path = search_path(path, shell);
			else
				path = ft_strdup(argv[0]);
			if (path == NULL && argv[0][0] != '\0')
				ft_dprintf(STDERR_FILENO, "minishell: command not found: %s\n", argv[0]);
			else if (access(path, F_OK) < 0 && argv[0][0] != '\0')
				ft_dprintf(STDERR_FILENO, "minishell: command not found: %s\n", argv[0]);
			free_argv(argv);
			free(path);
		}
		cur = cur->next;
	}
	free_node(cur);
}

int	exec(t_command *node, t_shell *shell)
{
	pid_t	last_pid;

	if (is_builtin(node) && node->next == NULL)
	{
		if (open_redirect_file(node, shell) < 0)
			return (1);
		return (exec_builtin(node, shell, node));
	}
	last_pid = exec_pipeline(node, shell, node);
	shell->last_status = wait_pipeline(last_pid);
	print_cmd_not_found(node, shell);
	return (shell->last_status);
}
