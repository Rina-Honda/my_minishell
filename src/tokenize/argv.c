/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:00:19 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/20 14:05:44 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**tail_recursive(t_token *token, int count, char **argv)
{
	int		i;
	char	**new_argv;

	if (token == NULL || token->kind == TK_EOF)
		return (argv);
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		fatal_error("malloc");
	i = 0;
	while (i < count)
	{
		new_argv[i] = argv[i];
		i++;
	}
	if (argv)
		free(argv);
	new_argv[i] = ft_strdup(token->word);
	if (new_argv[i] == NULL)
		fatal_error("ft_strdup");
	new_argv[i + 1] = NULL;
	return (tail_recursive(token->next, count + 1, new_argv));
}

char	**token_list_to_argv(t_token *token)
{
	char	**argv;

	argv = ft_calloc(1, sizeof(char *));
	if (argv == NULL)
		fatal_error("ft_calloc");
	return (tail_recursive(token, 0, argv));
}
