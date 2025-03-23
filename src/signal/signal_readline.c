/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:47:51 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/23 12:10:14 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_state(void)
{
	if (g_sig == 0)
		return (0);
	else if (g_sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
		return (0);
	}
	return (0);
}

bool	readline_sigint(t_shell *shell, char *line)
{
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		shell->last_status = 128 + SIGINT;
		free(line);
		return (true);
	}
	return (false);
}
