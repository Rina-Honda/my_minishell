/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:24:51 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:08:47 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*new_command(t_command_kind kind)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(*command));
	if (!command)
		fatal_error("ft_calloc");
	command->kind = kind;
	return (command);
}
