/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:00:09 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/25 01:28:57 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_path(const char *dir, const char *filename)
{
	char	candidte_path[PATH_MAX];
	char	*dup;

	ft_bzero(candidte_path, PATH_MAX);
	if (ft_strlen(dir) + 1 + ft_strlen(filename) < PATH_MAX)
	{
		ft_strlcat(candidte_path, dir, PATH_MAX);
		ft_strlcat(candidte_path, "/", PATH_MAX);
		ft_strlcat(candidte_path, filename, PATH_MAX);
		if (access(candidte_path, X_OK) == 0)
		{
			dup = ft_strdup(candidte_path);
			if (dup == NULL)
				fatal_error("ft_strdup");
			return (dup);
		}
	}
	return (NULL);
}

char	*search_path(const char *filename, t_shell *shell)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = ft_getenv("PATH", shell);
	while (*value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end && end - value + 1 < PATH_MAX)
			ft_strlcpy(path, value, end - value + 1);
		else
			ft_strlcpy(path, value, PATH_MAX);
		dup = build_path(path, filename);
		if (dup)
			return (dup);
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}
