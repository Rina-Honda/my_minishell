/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:30:51 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/09 13:32:12 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_cmd(t_command *command)
{
	// 環境変数グローバルで使える
	extern char	**environ;
	char		*path;
	pid_t		pid;
	int			wstatus;
	char		**argv;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	// child process
	if (pid == 0)
	{
		argv = token_list_to_argv(command->args);
		path = argv[0];
		// full pathじゃなかったら、$PATHでfull pathにする
		if (strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		// execve: pathnameをもとにファイル実行
		execve(path, argv, environ);
		fatal_error("execve");
	}
	// parent process
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

int	exec(t_command *command)
{
	int	status;

	if (open_redirect_file(command->redirects) < 0)
		return (ERROR_OPEN_REDIR);
	do_redirect(command->redirects);
	status = exec_cmd(command);
	reset_redirect(command->redirects);
	return (status);
}

void	interpret(char *line, int *status_loc)
{
	t_token		*token;
	t_command	*command;

	token = tokenize(line);
	if (at_eof(token))
		return ;
	else if (syntax_error)
		*status_loc = ERROR_TOKENIZE;
	else
	{
		command = parse(token);
		if (syntax_error)
			*status_loc = ERROR_PARSE;
		else
		{
			expand(command);
			*status_loc = exec(command);
		}
		free_command(command);
	}
	free_token(token);
}

int	main(void)
{
	char	*line;
	int		status;

	rl_outstream = stderr;
	status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		// lineが空の場合はadd_historyしない仕様
		if (*line)
			add_history(line);
		interpret(line, &status);
		free(line);
	}
	exit(status);
}
