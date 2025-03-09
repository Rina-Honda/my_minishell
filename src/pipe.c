/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:58:29 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/09 16:45:58 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe(t_command *node)
{
	if (!node->next)
		return ;
	if (pipe(node->outpipe) < 0)
		fatal_error("pipe");
	copy_pipe(node->next->inpipe, node->outpipe);
}

void	prepare_pipe_child(t_command *node)
{
	// 子プロセスでoutpipe読み取りを使わないのですぐ閉じる（outpipeは事前にpipe()してるので）
	close(node->outpipe[0]);
	// 子プロセスでinpipeの読み取りから読みたいので、STDINの中身をinpipeにする
	dup2(node->inpipe[0], STDIN_FILENO);
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	// 子プロセスでoutpipeの書き込みに書き込みたいので、STDOUTの中身をoutpipeにする
	dup2(node->outpipe[1], STDOUT_FILENO);
	if (node->outpipe[1] != STDOUT_FILENO)
		close(node->outpipe[1]);
}

void	prepare_pipe_parent(t_command *node)
{
	// 親プロセスでinpipeの読み取りを使わないのですぐ閉じる
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	// コマンドが最後だったら、親プロセスでoutpipeの書き込みを使わないので閉じる
	if (node->next)
		close(node->outpipe[1]);
}
