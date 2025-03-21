/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:21:21 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/21 21:30:14 by rhonda           ###   ########.fr       */
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

int	exec_builtin(t_command *current, t_shell *shell, t_command *node)
{
	int		status;
	char	**argv;

	printf("a\n");
	do_redirect(current->command->redirects);
	argv = token_list_to_argv(current->command->args);
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
	{
		printf("b\n");
		status = builtin_pwd(argv, shell);
	}
	else
		todo("exec_builtin");
	printf("d\n");
	free_argv(argv);
	printf("e\n");
	reset_redirect(current->command->redirects);
	printf("f\n");
	free_map(shell->envmap);
	printf("g\n");
	printf("builtin\n");
	free_node(node);
	printf("h\n");
	return (status);
}
