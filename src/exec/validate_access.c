/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:39:16 by msawada           #+#    #+#             */
/*   Updated: 2025/03/25 21:07:35 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	validate_access_free(char *path, char **argv)
{
	free(path);
	free_argv(argv);
}

void	validate_access(char *path, t_shell *shell, char **argv)
{
	if (path == NULL)
	{
		validate_access_free(path, argv);
		cmd_err_exit(127, shell);
	}
	if (access(path, F_OK) < 0)
	{
		validate_access_free(path, argv);
		cmd_err_exit(127, shell);
	}
}

void	validate_access_02(char *path, t_command *node, t_shell *shell,
		char **argv)
{
	struct stat	st;

	if (node->command->args->word[0] == '\0')
	{
		validate_access_free(path, argv);
		free_node(node);
		free_map(shell->envmap);
		exit(0);
	}
	if (stat(path, &st) == -1)
	{
		validate_access_free(path, argv);
		perror("stat error");
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(st.st_mode))
	{
		validate_access_free(path, argv);
		err_exit(node, "Is a directory", 126, shell);
	}
	if (access(path, X_OK) < 0)
	{
		validate_access_free(path, argv);
		err_exit(node, "Permission denied", 126, shell);
	}
}
