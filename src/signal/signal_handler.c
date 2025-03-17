/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:47:51 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 23:49:08 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_signum(int signum)
{
	sig = signum;
}

void	handler_newline(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}

void	ignore_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	reset_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}
