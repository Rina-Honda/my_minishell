/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:28:52 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 23:44:46 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirect(t_command *command)
{
	if (command->kind == REDIR_OUT)
		return (true);
	if (command->kind == REDIR_IN)
		return (true);
	if (command->kind == REDIR_APPEND)
		return (true);
	if (command->kind == REDIR_HEREDOC)
		return (true);
	return (false);
}

void	do_redirect(t_command *redirect)
{
	if (!redirect)
		return ;
	if (is_redirect(redirect))
	{
		redirect->stashed_targetfd = stashfd(redirect->targetfd);
		dup2(redirect->filefd, redirect->targetfd);
	}
	else
		assert_error("do_redirect");
	do_redirect(redirect->next);
}

void	reset_redirect(t_command *redirect)
{
	if (!redirect)
		return ;
	reset_redirect(redirect->next);
	if (is_redirect(redirect))
	{
		close(redirect->filefd);
		close(redirect->targetfd);
		dup2(redirect->stashed_targetfd, redirect->targetfd);
	}
	else
		assert_error("reset_redirect");
}
