/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:33:43 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:34 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node -> content = content;
	node -> next = NULL;
	return (node);
}

// #include <stdio.h>
// int main() {
//     // Create a new list node with content "Hello, World!"
//     t_list *node = NULL; //ft_lstnew("Hello, World!");

//     if (node == NULL) {
//         printf("Failed to create a new list node.\n");
//         return 1;
//     }

//     // Print the content of the newly created node
//     printf("Content: %s\n", (char *)node->content);

//     // Free the allocated memory for the node
//     free(node);

//     return 0;
// }