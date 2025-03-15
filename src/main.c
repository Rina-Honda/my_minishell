/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:30:51 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/15 19:28:39 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_status;

void	interpret(char *line, int *status_loc)
{
	t_token		*token;
	t_command	*node;

	token = tokenize(line);
	if (at_eof(token))
		return ;
	else if (syntax_error)
		*status_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(token);
		if (syntax_error)
			*status_loc = ERROR_PARSE;
		else
		{
			expand(node);
			*status_loc = exec(node);
		}
		free_node(node);
	}
	free_token(token);
}

int	main(void)
{
	char	*line;

	// rl_outstream = stderr;
	init_env();
	setup_signal();
	last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		// lineが空の場合はadd_historyしない仕様
		if (*line)
			add_history(line);
		interpret(line, &last_status);
		free(line);
	}
	exit(last_status);
}
