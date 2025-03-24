/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:58:38 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/24 21:42:15 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fatal_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

void	cmd_err_exit(t_command *node, int status, t_shell *shell)
{
	free_node(node);
	free_map(shell->envmap);
	exit(status);
}

void	err_exit(t_command *node, const char *msg, int status, t_shell *shell)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: %s\n", node->command->args->word, msg);
	free_node(node);
	free_map(shell->envmap);
	exit(status);
}

void	assert_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void	todo(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}
