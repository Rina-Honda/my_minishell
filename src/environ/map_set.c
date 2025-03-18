/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:52:27 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 10:01:26 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	map_item_update(t_item *item, const char *value)
{
	free(item->value);
	if (!value)
		item->value = NULL;
	else
	{
		item->value = ft_strdup(value);
		if (!item->value)
			fatal_error("map_set ft_strdup");
	}
}

static void	map_insert(t_map *map, const char *name, const char *value)
{
	t_item	*item;

	if (!value)
	{
		item = item_new(ft_strdup(name), NULL);
		if (!item->name)
			fatal_error("strdup");
	}
	else
	{
		item = item_new(ft_strdup(name), ft_strdup(value));
		if (!item->name || !item->value)
			fatal_error("ft_strdup");
	}
	item->next = map->item_head.next;
	map->item_head.next = item;
}

int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*current;

	if (!name || !is_identifier(name))
		return (-1);
	current = map_get(map, name);
	if (current)
		map_item_update(current, value);
	else
		map_insert(map, name, value);
	return (0);
}
