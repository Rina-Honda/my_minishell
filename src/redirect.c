/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:28:52 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/09 11:17:47 by rhonda           ###   ########.fr       */
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

int	open_redirect_file(t_command *redirect)
{
	// nodeの終端で return (0)
	if (!redirect)
		return (0);
	if (redirect->kind == REDIR_OUT)
		redirect->filefd = open(redirect->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redirect->kind == REDIR_IN)
		redirect->filefd = open(redirect->filename->word, O_RDONLY);
	else
		todo("open_redirect_file");
	// open error
	if (redirect->filefd < 0)
	{
		xperror(redirect->filename->word);
		return (-1);
	}
	redirect->filefd = stashfd(redirect->filefd);
	// redirect fileがまだあればopenする
	return (open_redirect_file(redirect->next));
}

void	do_redirect(t_command *redirect)
{
	if (!redirect)
		return ;
	if (redirect->kind == REDIR_OUT || redirect->kind == REDIR_IN)
	{
		redirect->stashed_targetfd = stashfd(redirect->targetfd);
		// dup2(old_fd, new_fd); new_fdの中身が、old_fdの中身に書き変わる
		// つまりSTDIN, STDOUTの中身がopenしたfilefdに書き変わる
		dup2(redirect->filefd, redirect->targetfd);
	}
	else
		todo("do_redirect");
	// redirectの連鎖を処理
	do_redirect(redirect->next);
}

void	reset_redirect(t_command *redirect)
{
	if (!redirect)
		return ;
	// 再帰にすることで、最後のredirectからresetできる
	reset_redirect(redirect->next);
	if (redirect->kind == REDIR_OUT || redirect->kind == REDIR_IN)
	{
		close(redirect->filefd);
		close(redirect->targetfd);
		// 空いたtargetfdに、stashしておいたdup前のtargetfdをセットする
		dup2(redirect->stashed_targetfd, redirect->targetfd);
	}
	else
		todo("reset_redirect");
}
