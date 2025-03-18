/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:23:38 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 09:06:44 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	update_oldpwd(char *old_pwd)
{
	if (!old_pwd)
		map_set(envmap, "OLDPWD", "");
	else
		map_set(envmap, "OLDPWD", old_pwd);
}

int	set_path(char *path, size_t path_size, char *arg)
{
	char	*home;

	if (!arg)
	{
		home = ft_getenv("HOME");
		if (!home)
		{
			builtin_error("cd", NULL, "$HOME not set");
			return (-1);
		}
		ft_strlcpy(path, home, path_size);
	}
	else
		ft_strlcpy(path, arg, path_size);
	return (0);
}

int	builtin_cd(char **argv)
{
	char	*old_pwd;
	char	path[PATH_MAX];
	char	*new_pwd;

	if (count_words(argv) > 2)
	{
		builtin_error("cd", NULL, "too many arguments");
		return (1);
	}
	old_pwd = ft_getenv("PWD");
	update_oldpwd(old_pwd);
	if (set_path(path, PATH_MAX, argv[1]) < 0)
		return (1);
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
