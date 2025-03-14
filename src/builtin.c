/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:21:21 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/14 21:34:51 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_command *node)
{
	const char		*cmd_name;
	char			*builtin_commands[] = {"exit", "export", "unset"};
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
		if (strcmp(cmd_name, builtin_commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_command *node)
{
	int		status;
	char	**argv;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	if (strcmp(argv[0], "exit") == 0)
		status = builtin_exit(argv);
	else if (strcmp(argv[0], "export") == 0)
		status = builtin_export(argv);
	else if (strcmp(argv[0], "unset") == 0)
		status = builtin_unset(argv);
	else
		todo("exec_builtin");
	free_argv(argv);
	reset_redirect(node->command->redirects);
	return (status);
}
