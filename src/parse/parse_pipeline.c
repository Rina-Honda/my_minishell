/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:27:08 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 17:57:05 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*pipeline(t_token **rest, t_token *token, t_shell *shell)
{
	t_command	*node;

	node = new_command(PIPELINE);
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->command = simple_command(&token, token, shell);
	if (equal_operator(token, "|"))
		node->next = pipeline(&token, token->next, shell);
	*rest = token;
	return (node);
}
