/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:00:19 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/23 13:15:53 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(char **argv, t_shell *shell)
{
	t_item	*current;

	(void)argv;
	current = shell->envmap->item_head.next;
	while (current)
	{
		if (current->value)
			ft_dprintf(STDOUT_FILENO, "%s=%s\n", current->name, current->value);
		current = current->next;
	}
	ft_dprintf(STDOUT_FILENO, "_=/usr/bin/env\n");
	return (0);
}
