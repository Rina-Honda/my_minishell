/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:00:09 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 23:00:37 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = ft_getenv("PATH");
	while (*value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end && end - value + 1 < PATH_MAX)
			ft_strlcpy(path, value, end - value + 1);
		else
			ft_strlcpy(path, value, PATH_MAX);
		if (ft_strlen(path) + 1 + ft_strlen(filename) < PATH_MAX)
		{
			ft_strlcat(path, "/", PATH_MAX);
			ft_strlcat(path, filename, PATH_MAX);
			if (access(path, X_OK) == 0)
			{
				dup = ft_strdup(path);
				if (dup == NULL)
					fatal_error("ft_strdup");
				return (dup);
			}
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}
