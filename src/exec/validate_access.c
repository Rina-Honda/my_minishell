/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:39:16 by msawada           #+#    #+#             */
/*   Updated: 2025/03/25 18:41:04 by msawada          ###   ########.fr       */
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

void	validate_access_02(const char *path, t_command *node, t_shell *shell,
		char **argv)
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
