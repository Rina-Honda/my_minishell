/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:16:59 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:00:50 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	perror_prefix(void)
{
	dprintf(STDERR_FILENO, "%s", "minishell: ");
}

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}

void	builtin_error(const char *func, const char *name, const char *err)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "%s: ", func);
	if (name)
		dprintf(STDERR_FILENO, "`%s: ", name);
	dprintf(STDERR_FILENO, "%s\n", err);
}
