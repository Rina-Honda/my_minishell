/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:30:51 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/21 21:37:24 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interpret(char *line, t_shell *shell)
{
	t_token		*token;
	t_command	*node;

	token = tokenize(line, shell);
	if (at_eof(token))
		free_token(token);
	else if (shell->syntax_error)
	{
		free_token(token);
		shell->last_status = ERROR_TOKENIZE;
	}
	else
	{
		node = parse(token, shell);
		free_token(token);
		if (shell->syntax_error)
			shell->last_status = ERROR_PARSE;
		else
		{
			expand(node, shell);
			shell->last_status = exec(node, shell);
		}
		free_node(node);
	}
}

int	main(void)
{
	char	*line;
	t_shell	shell;

	shell.last_status = 0;
	shell.syntax_error = false;
	shell.readline_interrupted = false;
	init_env(&shell);
	setup_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &shell);
		free(line);
	}
	rl_clear_history();
	free_map(shell.envmap);
	exit(shell.last_status);
}
