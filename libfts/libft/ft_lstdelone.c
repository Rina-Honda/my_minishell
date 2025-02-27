/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:42:12 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:18 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst -> content);
	free(lst);
}

// // Sample content deletion function
// void free_content(void *content)
// {
// 	// Add your content deletion logic here
// 	free(content);
// }

// #include <string.h>
// int main()
// {
// 	// Create test data
// 	char *data = strdup("Test data");

// 	// Create a test t_list element
// 	t_list *node = ft_lstnew(data);

// 	if (node == NULL)
// 	{
// 		perror("Failed to create a new list node");
// 		return (1);
// 	}

// 	// Delete the test t_list element
// 	ft_lstdelone(node, free_content);

// 	return (0);
// }

// #include <stdlib.h>
// #include <stdio.h>

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }				t_list;

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*node;

// 	node = (t_list *)malloc(sizeof(t_list));
// 	if (node == NULL)
// 		return (NULL);
// 	node -> content = content;
// 	node -> next = NULL;
// 	return (node);
// }