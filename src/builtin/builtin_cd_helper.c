/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:07:01 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 09:32:40 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	consume_path(char **rest, char *path, char *elem)
{
	size_t	elem_len;

	elem_len = ft_strlen(elem);
	if (ft_strncmp(path, elem, elem_len) == 0)
	{
		if (path[elem_len] == '\0' || path[elem_len] == '/')
		{
			*rest = path + elem_len;
			return (true);
		}
	}
	return (false);
}

void	delete_last_elem(char *path)
{
	char	*start;
	char	*last_slash_ptr;

	start = path;
	last_slash_ptr = NULL;
	while (*path)
	{
		if (*path == '/')
			last_slash_ptr = path;
		path++;
	}
	if (last_slash_ptr != start)
		*last_slash_ptr = '\0';
}

static void	append_path_elem(char *dst, size_t dst_size,
		char **rest, char *src)
{
	size_t	dst_len;
	size_t	elem_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	elem_len = 0;
	while (src[elem_len] && src[elem_len] != '/')
		elem_len++;
	if (dst_len == 0 || dst[dst_len - 1] != '/')
	{
		if (dst_len < dst_size - 1)
		{
			dst[dst_len] = '/';
			dst[dst_len + 1] = '\0';
			dst_len++;
		}
		else
			return ;
	}
	i = 0;
	while (i < elem_len && dst_len < dst_size - 1)
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
	}
	dst[dst_len] = '\0';
	*rest = src + elem_len;
}

char	*resolve_pwd(char *old_pwd, char *path)
{
	char	new_pwd[PATH_MAX];
	char	*dup;

	if (!old_pwd)
		return (NULL);
	if (*path == '/')
		ft_strlcpy(new_pwd, "/", PATH_MAX);
	else
		ft_strlcpy(new_pwd, old_pwd, PATH_MAX);
	while (*path)
	{
		if (*path == '/')
			path++;
		else if (consume_path(&path, path, "."))
			;
		else if (consume_path(&path, path, ".."))
			delete_last_elem(new_pwd);
		else
			append_path_elem(new_pwd, PATH_MAX, &path, path);
	}
	dup = ft_strdup(new_pwd);
	if (!dup)
		fatal_error("ft_strdup");
	return (dup);
}
