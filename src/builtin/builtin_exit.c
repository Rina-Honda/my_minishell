/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:16:58 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/24 15:05:41 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_numeric(char *s)
{
	if (!s || *s == '\0')
		return (false);
	if (*s == '+' || *s == '-')
		s++;
	if (!ft_isdigit(*s))
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

static void	free_all(char *arg, t_command *node, t_shell *shell)
{
	if (arg)
		free(arg);
	if (shell->envmap)
		free_map(shell->envmap);
	if (node)
		free_node(node);
}

// TODO 関数を分割する
int	builtin_exit(char **argv, t_shell *shell, t_command *node)
{
	long	result;
	char	*arg;
	char	*end_ptr;

	arg = NULL;
	if (!argv[1])
	{
		free_all(arg, node, shell);
		free_argv(argv);
		exit(shell->last_status);
	}
	if (argv[2])
	{
		builtin_error("exit", NULL, "too many arguments");
		return (1);
	}
	arg = argv[1];
	if (is_numeric(arg))
	{
		errno = 0;
		result = ft_strtol(arg, &end_ptr, 10);
		if (errno == 0 && *end_ptr == '\0')
		{
			free_all(arg, node, shell);
			exit((unsigned char)result);
		}
	}
	free_all(arg, node, shell);
	builtin_error("exit", NULL, "numeric argument required");
	exit(2);
}
