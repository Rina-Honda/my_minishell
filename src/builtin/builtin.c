/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:21:21 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/20 19:01:23 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(t_command *node)
{
	const char		*cmd_name;
	const char		*builtin_commands[] = {"exit", "export",
		"unset", "env", "cd", "echo", "pwd"};
	unsigned int	i;

	if (!node)
		return (false);
	else if (!node->command)
		return (false);
	else if (!node->command->args)
		return (false);
	else if (!node->command->args->word)
		return (false);
	cmd_name = node->command->args->word;
	if (!cmd_name)
		return (false);
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (ft_strcmp(cmd_name, builtin_commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_command *node, t_shell *shell)
{
	int		status;
	char	**argv;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	if (ft_strcmp(argv[0], "exit") == 0)
		status = builtin_exit(argv, shell, node);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = builtin_export(argv, shell);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = builtin_unset(argv, shell);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = builtin_env(argv, shell);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = builtin_cd(argv, shell);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = builtin_echo(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = builtin_pwd(argv, shell);
	else
		todo("exec_builtin");
	free_argv(argv);
	reset_redirect(node->command->redirects);
	free_map(shell->envmap);
	free_node(node);
	return (status);
}
