/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:21:44 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/25 21:15:11 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_map	*map_new(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(*map));
	if (!map)
		fatal_error("calloc");
	return (map);
}

t_item	*map_get(t_map *map, const char *name)
{
	t_item	*current;

	if (!name)
		return (NULL);
	current = map->item_head.next;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

size_t	map_len(t_map *map, bool count_null_value)
{
	size_t	len;
	t_item	*item;

	len = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value || count_null_value)
			len++;
		item = item->next;
	}
	return (len);
}

int	map_unset(t_map *map, const char *name)
{
	t_item	*current;
	t_item	*prev;

	if (!name || !is_identifier(name))
		return (-1);
	prev = &map->item_head;
	current = map->item_head.next;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			prev->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		prev = prev->next;
		current = current->next;
	}
	return (0);
}
