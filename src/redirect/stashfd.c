/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stashfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:41:50 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/20 13:50:49 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dup_stash(int fd, int min_fd)
{
	char	*candidate_str;
	char	path[PATH_MAX];
	int		stash_fd;

	if (min_fd < 0)
		return (-1);
	while (min_fd < OPEN_MAX)
	{
		path[0] = '\0';
		candidate_str = ft_itoa(min_fd);
		ft_strlcat(path, "/proc/self/fd/", PATH_MAX);
		ft_strlcat(path, candidate_str, PATH_MAX);
		free(candidate_str);
		if (access(path, F_OK) == -1)
		{
			stash_fd = dup2(fd, min_fd);
			if (stash_fd < 0)
				return (-1);
			return (stash_fd);
		}
		min_fd++;
	}
	errno = EMFILE;
	return (-1);
}

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = dup_stash(fd, 10);
	if (stashfd < 0)
		fatal_error("dup_stash");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}
