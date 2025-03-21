/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:35:06 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/21 21:38:35 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->word)
		free(token->word);
	free_token(token->next);
	free(token);
}

void	free_argv(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_node(t_command *node)
{
	if (!node)
		return ;
	free_token(node->args);
	free_token(node->filename);
	free_token(node->delimiter);
	free_node(node->redirects);
	free_node(node->command);
	free_node(node->next);
	free(node);
}

static void	free_item(t_item *item)
{
	if (!item)
		return ;
	if (item->name)
		free(item->name);
	if (item->value)
		free(item->value);
	free_item(item->next);
	free(item);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_item(map->item_head.next);
	free(map);
}
