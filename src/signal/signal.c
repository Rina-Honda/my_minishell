/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:54:38 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:08:57 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	sig = 0;

int	check_state()
{
	if (sig == 0)
		return (0);
	else if (sig == SIGINT)
	{
		sig = 0;
		readline_interrupted = true;
		rl_replace_line("", 0);
		rl_done = 1;
		return (0);
	}
	return (0);
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

void	handler_signum(int signum)
{
	sig = signum;
}

void	handler_newline(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}

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
	sa.sa_flags = 0;
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

void	reset_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	reset_signal(void)
{
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
}
