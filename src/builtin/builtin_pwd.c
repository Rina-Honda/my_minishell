/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:15:18 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/22 22:41:00 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_equal_inode(const char *path1, const char *path2)
{
	struct stat	st1;
	struct stat	st2;

	ft_memset(&st1, 0, sizeof(st1));
	ft_memset(&st2, 0, sizeof(st2));
	if (stat(path1, &st1) < 0 || stat(path2, &st2) < 0)
		return (false);
	return (st1.st_ino == st2.st_ino);
}


int	builtin_pwd(char **argv, t_shell *shell)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)argv;
	pwd = ft_getenv("PWD", shell);
	if (!pwd || !is_equal_inode(pwd, "."))
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			builtin_error("pwd", NULL, "getcwd");
			return (1);
		}
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
}
