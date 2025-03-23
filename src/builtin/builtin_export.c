/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:48:40 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/24 00:13:54 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_all_env(t_shell *shell)
{
	t_item	*current;

	current = shell->envmap->item_head.next;
	while (current)
	{
		if (current->value)
			ft_dprintf(STDOUT_FILENO,
				"declare -x %s=\"%s\"\n", current->name, current->value);
		else
			ft_dprintf(STDOUT_FILENO, "declare -x %s\n", current->name);
		current = current->next;
	}
}

int	builtin_export(char **argv, t_shell *shell)
{
	size_t	i;
	int		status;

	if (!argv[1])
	{
		print_all_env(shell);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_put(shell->envmap, argv[i], true) < 0)
		{
			builtin_error("export", argv[i], "not a valid identifier");
			status = 1;
		}
		i++;
	}
	return (status);
}
