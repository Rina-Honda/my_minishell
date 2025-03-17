/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:52:27 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:53:04 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*current;

	if (!name || !is_identifier(name))
		return (-1);
	current = map->item_head.next;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			break ;
		current = current->next;
	}
	if (current)
	{
		free(current->value);
		if (!value)
			current->value = NULL;
		else
		{
			current->value = ft_strdup(value);
			if (!current->value)
				fatal_error("ft_strdup");
		}
	}
	else
	{
		if (!value)
		{
			current = item_new(ft_strdup(name), NULL);
			if (!current->name)
				fatal_error("strdup");
		}
		else
		{
			current = item_new(ft_strdup(name), ft_strdup(value));
			if (!current->name || !current->value)
				fatal_error("ft_strdup");
		}
		current->next = map->item_head.next;
		map->item_head.next = current;
	}
	return (0);
}
