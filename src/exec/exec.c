/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:55:46 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/25 20:10:29 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_cmd(char **argv, t_command *node, t_shell *shell)
{
	free_argv(argv);
	free_node(node);
	free_map(shell->envmap);
	exit(EXIT_FAILURE);
}

int	exec_nonbuiltin(t_command *node, t_shell *shell)
{
	char	*path;
	char	**argv;
	char	**env;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	if (!argv || !argv[0] || argv[0][0] == '\0')
		skip_cmd(argv, node, shell);
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

static void	child_exec_pipeline_process(t_command *current,
	t_command *node, t_shell *shell)
{
	int		status;

	setup_sigint_with_signum();
	if (open_redirect_file(current, shell) < 0)
	{
		free_node(shell->node_head);
		free_map(shell->envmap);
		exit(EXIT_FAILURE);
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

static pid_t	exec_pipeline(t_command *current, t_shell *shell,
		t_command *node)
{
	pid_t	pid;

	if (!current)
		return (-1);
	prepare_pipe(current);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
		child_exec_pipeline_process(current, node, shell);
	prepare_pipe_parent(current);
	if (current->next)
		return (exec_pipeline(current->next, shell, node));
	return (pid);
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
