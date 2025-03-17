/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:21:44 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:57:15 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_map	*map_new(void)
{
	t_map	*map;

	// mapのポインタではなく中身分確保
	map = calloc(1, sizeof(*map));
	if (!map)
		fatal_error("calloc");
	return (map);
}

int	map_put(t_map *map, const char *str, bool allow_empty_value)
{
	int		result;
	char	*name_end;
	char	*name;
	char	*value;

	name_end = ft_strchr(str, '=');
	if (!name_end)
	{
		if (!allow_empty_value)
			return (-1);
		name = ft_strdup(str);
		value = NULL;
		if (!name)
			fatal_error("ft_strdup");
	}
	else
	{
		name = strndup(str, name_end - str);
		value = ft_strdup(name_end + 1);
		if (!name || !value)
			fatal_error("ft_strdup");
	}
	result = map_set(map, name, value);
	free(name);
	free(value);
	return (result);
}

char	*map_get(t_map *map, const char *name)
{
	t_item	*current;

	if (!name)
		return (NULL);
	current = map->item_head.next;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
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
			// freeの前に前後をつなげとく
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
