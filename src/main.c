/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:30:51 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/10 00:10:35 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_status;

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = getenv("PATH");
	// printf("value: %s\n", value);
	while (*value)
	{
		ft_bzero(path, PATH_MAX);
		//区切り文字を探す
		end = ft_strchr(value, ':');
		//ヌル終端保証
		if (end && end - value + 1 < PATH_MAX)
			ft_strlcpy(path, value, end - value + 1);
		else
			ft_strlcpy(path, value, PATH_MAX);
		if (ft_strlen(path) + 1 + ft_strlen(filename) < PATH_MAX)
		{
			ft_strlcat(path, "/", PATH_MAX);
			ft_strlcat(path, filename, PATH_MAX);
			if (access(path, X_OK) == 0)
			{
				char	*dup;
				dup = ft_strdup(path);
				if (dup == NULL)
					fatal_error("ft_strdup");
				return (dup);
			}
		}
		//実行できるやつが見つからず最後のエントリまで見切った時
		if (end == NULL)
			return (NULL);
		//次のエントリに更新
		value = end + 1;
	}
	return (NULL);
}

void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

pid_t	exec_pipeline(t_command *node)
{
	// 環境変数グローバルで使える
	extern char	**environ;
	char		*path;
	pid_t		pid;
	char		**argv;

	if (!node)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	// fork error
	if (pid < 0)
		fatal_error("fork");
	// child process
	else if (pid == 0)
	{
		prepare_pipe_child(node);
		do_redirect(node->command->redirects);
		argv = token_list_to_argv(node->command->args);
		path = argv[0];
		// full pathじゃなかったら、$PATHでfull pathにする
		if (strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		// execve: pathnameをもとにファイル実行
		execve(path, argv, environ);
		reset_redirect(node->command->redirects);
		fatal_error("execve");
	}
	// parent process
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next));
	// last_pidを返す
	return (pid);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
			status = WEXITSTATUS(wstatus);
		// child processがいなくなったら
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	return (status);
}

int	exec(t_command *node)
{
	pid_t	last_pid;
	int		status;

	if (open_redirect_file(node) < 0)
		return (ERROR_OPEN_REDIR);
	last_pid = exec_pipeline(node);
	status = wait_pipeline(last_pid);
	return (status);
}

void	interpret(char *line, int *status_loc)
{
	t_token		*token;
	t_command	*node;

	token = tokenize(line);
	if (at_eof(token))
		return ;
	else if (syntax_error)
		*status_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(token);
		if (syntax_error)
			*status_loc = ERROR_PARSE;
		else
		{
			expand(node);
			*status_loc = exec(node);
		}
		free_node(node);
	}
	free_token(token);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		// lineが空の場合はadd_historyしない仕様
		if (*line)
			add_history(line);
		interpret(line, &last_status);
		free(line);
	}
	exit(last_status);
}
