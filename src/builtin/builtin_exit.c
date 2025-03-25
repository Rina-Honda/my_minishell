/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:16:58 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/25 19:10:21 by msawada          ###   ########.fr       */
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

static void	free_all(char **argv, t_command *node, t_shell *shell)
{
	if (argv)
		free_argv(argv);
	if (shell->envmap)
		free_map(shell->envmap);
	if (node)
		free_node(node);
}

static int	check_exit_argument_error(char **argv)
{
	if (argv[2])
	{
		builtin_error("exit", NULL, "too many arguments");
		return (1);
	}
	return (0);
}

static int	parse_exit_argument(char *arg, long *result)
{
	char	*end_ptr;

	if (!is_numeric(arg))
		return (0);
	errno = 0;
	*result = ft_strtol(arg, &end_ptr, 10);
	if (errno == 0 && *end_ptr == '\0')
		return (1);
	return (0);
}

int	builtin_exit(char **argv, t_shell *shell, t_command *node)
{
	long	result;
	char	*arg;

	arg = NULL;
	if (!argv[1])
	{
		free_all(argv, node, shell);
		exit(shell->last_status);
	}
	if (check_exit_argument_error(argv))
		return (1);
	if (parse_exit_argument(argv[1], &result))
	{
		free_all(argv, node, shell);
		exit((unsigned char)result);
	}
	free_all(argv, shell->node_head, shell);
	builtin_error("exit", NULL, "numeric argument required");
	exit(2);
}
