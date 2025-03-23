/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:00:09 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/23 16:16:25 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	check_wait_end(pid_t *wait_result,
		int wstatus, pid_t *last_pid, int *status)
{
	if (*wait_result == *last_pid)
	{
		if (WIFSIGNALED(wstatus))
			*status = 128 + WTERMSIG(wstatus);
		else
			*status = WEXITSTATUS(wstatus);
		return (true);
	}
	else if (*wait_result < 0)
	{
		if (errno == ECHILD)
			return (true);
		else if (errno == EINTR)
			return (false);
		else
			fatal_error("wait");
	}
	return (false);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	setup_sigint_newline();
	while (1)
	{
		wait_result = wait(&wstatus);
		if (check_wait_end(&wait_result, wstatus, &last_pid, &status))
			break ;
	}
	setup_sigint_with_signum();
	return (status);
}
