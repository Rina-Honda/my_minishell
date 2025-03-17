/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:54:48 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:35:42 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*item_get_string(t_item *item)
{
	size_t	str_size;
	char	*str;

	str_size = ft_strlen(item->name) + 2;
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
