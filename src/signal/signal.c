/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:54:38 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/25 18:03:08 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	setup_sigint_with_signum(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler_signum;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	setup_sigint_newline(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler_newline;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	setup_signal(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	ignore_sig(SIGQUIT);
	setup_sigint_with_signum();
}

void	reset_signal(void)
{
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
}
