/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:48:40 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:02:43 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_all_env(void)
{
	t_item	*current;
	current = envmap->item_head.next;
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
}

int	builtin_export(char **argv)
{
	size_t	i;
	int		status;

	if (!argv[1])
	{
		print_all_env();
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_put(envmap, argv[i], true) < 0)
		{
			builtin_error("export", argv[i], "not a valid identifier");
			status = 1;
		}
		i++;
	}
	return (status);
}
