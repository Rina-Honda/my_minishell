/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:21:44 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/14 21:32:32 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*map_new(void)
{
	t_map	*map;

	// mapのポインタではなく中身分確保
	map = calloc(1, sizeof(*map));
	if (!map)
		fatal_error("calloc");
	return (map);
}

bool	is_identifier(const char *s)
{
	if (!is_alpha_underscore(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_underscore(*s))
			return (false);
		s++;
	}
	return (true);
}

t_item	*item_new(char *name, char *value)
{
	t_item	*item;

	item = ft_calloc(1, sizeof(*item));
	if (!item)
		fatal_error("ft_calloc");
	item->name = name;
	item->value = value;
	return (item);
}

int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*current;

	if (!name || !is_identifier(name))
		return (-1);
	current = map->item_head.next;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
			break ;
		current = current->next;
	}
	// found name
	if (current)
	{
		// valueを上書き
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
	// 404 not found
	else
	{
		// item 新規作成
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
		// mapの先頭に新規itemを追加
		current->next = map->item_head.next;
		map->item_head.next = current;
	}
	return (0);
}

int	map_put(t_map *map, const char *str, bool allow_empty_value)
{
	int		result;
	char	*name_end;
	char	*name;
	char	*value;

	name_end = ft_strchr(str, '=');
	// none value
	if (!name_end)
	{
		if (!allow_empty_value)
			return (-1);
		name = ft_strdup(str);
		value = NULL;
		if (!name)
			fatal_error("ft_strdup");
	}
	// value exist
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
		if (strcmp(current->name, name) == 0)
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

char	*item_get_string(t_item *item)
{
	size_t	str_size;
	char	*str;

	str_size = ft_strlen(item->name) + 2; // イコールと\0の分
	if (item->value)
		str_size += ft_strlen(item->value);
	str = malloc(sizeof(char) * str_size);
	if (!str)
		fatal_error("malloc");
	ft_strlcpy(str, item->name, str_size);
	if (item->value)
	{
		ft_strlcat(str, "=", str_size);
		ft_strlcat(str, item->value, str_size);
	}
	return (str);
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
		if (strcmp(current->name, name) == 0)
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
