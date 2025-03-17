/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:17:03 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:18:51 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_map	*envmap;

static void	init_envmap(t_map *map, char **envp)
{
	while (*envp)
	{
		map_put(map, *envp, false);
		envp++;
	}
}

void	init_env(void)
{
	extern char	**environ;

	envmap = map_new();
	init_envmap(envmap, environ);
}

char	*ft_getenv(const char *name)
{
	return (map_get(envmap, name));
}

char	**get_environ(t_map *map)
{
	size_t	i;
	size_t	size;
	t_item	*item;
	char	**environ;

	size = map_len(map, false) + 1;
	environ = ft_calloc(size, sizeof(char *));
	if (!environ)
		fatal_error("ft_calloc");
	i = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value)
		{
			environ[i] = item_get_string(item);
			i++;
		}
		item = item->next;
	}
	environ[i] = NULL;
	return (environ);
}
