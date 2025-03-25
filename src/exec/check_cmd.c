/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:06:36 by msawada           #+#    #+#             */
/*   Updated: 2025/03/25 20:43:10 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_cmd_not_found(t_command *cur, t_shell *shell)
{
	char	*path;
	char	**argv;

	if (!cur->command || !cur->command->args)
		return ;
	argv = token_list_to_argv(cur->command->args);
	path = argv[0];
	if (ft_strchr(path, '/') == NULL)
		path = search_path(path, shell);
	else
		path = ft_strdup(argv[0]);
	if (path == NULL && argv[0][0] != '\0')
		ft_dprintf(STDERR_FILENO, "minishell: command not found: %s\n",
			argv[0]);
	else if (access(path, F_OK) < 0 && argv[0][0] != '\0')
		ft_dprintf(STDERR_FILENO, "minishell: command not found: %s\n",
			argv[0]);
	free_argv(argv);
	free(path);
}

void	print_cmd_not_found(t_command *node, t_shell *shell)
{
	t_command	*cur;

	cur = node;
	while (cur)
	{
		if (!is_builtin(cur))
			check_cmd_not_found(cur, shell);
		cur = cur->next;
	}
}
