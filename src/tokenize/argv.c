/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:00:19 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:00:56 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**tail_recursive(t_token *token, int count, char **argv)
{
	if (token == NULL || token->kind == TK_EOF)
		return (argv);
	argv = realloc(argv, (count + 2) * sizeof(char *));
	argv[count] = ft_strdup(token->word);
	if (argv[count] == NULL)
		fatal_error("ft_strdup");
	argv[count + 1] = NULL;
	return (tail_recursive(token->next, count + 1, argv));
}

char	**token_list_to_argv(t_token *token)
{
	char	**argv;

	argv = ft_calloc(1, sizeof(char *));
	if (argv == NULL)
		fatal_error("ft_calloc");
	return (tail_recursive(token, 0, argv));
}
