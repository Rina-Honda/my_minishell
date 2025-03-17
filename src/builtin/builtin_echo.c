/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:51 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:03:06 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(char **argv)
{
	bool	is_first_arg;
	bool	echo_newline;
	size_t	i;

	i = 1;
	echo_newline = true;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		echo_newline = false;
		i++;
	}
	is_first_arg = true;
	while (argv[i])
	{
		if (!is_first_arg)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		is_first_arg = false;
		i++;
	}
	if (echo_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
