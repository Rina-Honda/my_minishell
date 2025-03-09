/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:28:52 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/09 01:10:22 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

void	open_redirect_file(t_command *redirect)
{
	if (!redirect)
		return ;
	if (redirect->kind == REDIR_OUT)
		redirect->filefd = open(redirect->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		todo("open_redirect_file");
	redirect->filefd = stashfd(redirect->filefd);
	// redirect fileがまだあればopenする
	open_redirect_file(redirect->next);
}

void	do_redirect(t_command *redirect)
{
	if (!redirect)
		return ;
	if (redirect->kind == REDIR_OUT)
	{
		redirect->stashed_targetfd = stashfd(redirect->targetfd);
		// dup2(old_fd, new_fd); new_fdの中身が、old_fdの中身に書き変わる
		dup2(redirect->filefd, redirect->targetfd);
	}
	// redirectの連鎖を処理
	do_redirect(redirect->next);
}

void	reset_redirect(t_command *redirect)
{
	if (!redirect)
		return ;
	// 再帰にすることで、最後のredirectからresetできる
	reset_redirect(redirect->next);
	if (redirect->kind == REDIR_OUT)
	{
		close(redirect->filefd);
		close(redirect->targetfd);
		// targetfdにstashしておいたtargetfdをセットする
		dup2(redirect->stashed_targetfd, redirect->targetfd);
	}
}
