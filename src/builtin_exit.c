/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:16:58 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/15 20:31:26 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_numeric(char *s)
{
	if (!s || *s == '\0' || !ft_isdigit(*s))
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

int	builtin_exit(char **argv)
{
	long 	result;
	char	*arg;
	char	*end_ptr;

	// none argv
	if (!argv[1])
		exit(last_status);
	if (argv[2])
	{
		builtin_error("exit", NULL,"too many arguments");
		return (1);
	}
	arg = argv[1];
	if (is_numeric(arg))
	{
		errno = 0;
		result = strtol(arg, &end_ptr, 10);
		if (errno == 0 && *end_ptr == '\0')
			exit((int)result);
	}
	xperror("exit: numeric argment required");
	exit(255); //? code環境によって違う？
}
