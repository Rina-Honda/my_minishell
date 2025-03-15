/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:23:38 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/15 20:08:18 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	consume_path(char **rest, char *path, char *elem)
{
	size_t	elem_len;

	elem_len = ft_strlen(elem);
	// 配下のディレクトリの時
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

void	append_path_elem(char *dst, size_t dst_size, char **rest, char *src)
{
	size_t	dst_len;
	size_t	elem_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	elem_len = 0;
	while (src[elem_len] && src[elem_len] != '/')
		elem_len++;
	//? 初回か、末尾が/でないときに/を追加
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

size_t	count_words(char **argv)
{
	size_t	count;

	count = 0;
	if (!argv || !argv[count])
		return (0);
	while (argv[count])
		count++;
	return (count);
}

int	builtin_cd(char **argv)
{
	char	*home;
	char	*old_pwd;
	char	path[PATH_MAX];
	char	*new_pwd;

	if (count_words(argv) > 2)
	{
		builtin_error("cd", NULL, "too many arguments");
		return (1);
	}
	old_pwd = map_get(envmap, "PWD");
	map_set(envmap, "OLDPWD", old_pwd);
	// 引数なしは$HOMEへ移動
	if (!argv[1])
	{
		home = map_get(envmap, "HOME");
		if (!home)
		{
			builtin_error("cd", NULL, "$HOME not set");
			return (1);
		}
		ft_strlcpy(path, home, PATH_MAX); //? checkいらん？
	}
	else
		ft_strlcpy(path, argv[1], PATH_MAX); //? checkいらん？
	if (chdir(path) < 0)
	{
		if (errno == ENOENT)
			builtin_error("cd", argv[1], "No such file or directory");
		else
			builtin_error("cd", NULL, "chdir");
		return (1);
	}
	new_pwd = resolve_pwd(old_pwd, path);
	map_set(envmap, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}
