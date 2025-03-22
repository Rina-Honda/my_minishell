/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:18:57 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/22 11:29:56 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*parse(t_token *token, t_shell *shell)
{
	t_command	*node_head;

	node_head = pipeline(&token, token, shell);
	shell->node_head = node_head;
	return (node_head);
}
