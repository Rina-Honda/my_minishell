/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:18:57 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/23 23:22:17 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*parse(t_token *token, t_shell *shell)
{
	shell->node_head = pipeline(&token, token, shell);
	return (shell->node_head);
}
