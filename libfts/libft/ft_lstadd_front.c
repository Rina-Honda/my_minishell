/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:46:41 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:10 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != NULL && new != NULL)
	{
		new -> next = *lst;
		*lst = new;
	}
}

// #include <stdio.h>
// int main() {
//     // Create a new list node with content "Node 2"
//     t_list *node2 = ft_lstnew("Node 2");

//     if (node2 == NULL) {
//         printf("Failed to create a new list node.\n");
//         return 1;
//     }

//     // Create an initial list node with content "Node 1"
//     t_list *node1 = ft_lstnew("Node 1");

//     if (node1 == NULL) {
//         printf("Failed to create a new list node.\n");
//         free(node2);
//         return 1;
//     }

//     // Initialize the list with the first node
//     t_list *list = node1;

//     // Add the second node to the front of the list
//     ft_lstadd_front(&list, node2);

//     // Print the contents of the list
//     t_list *current = list;
//     while (current != NULL) {
//         printf("Content: %s\n", (char *)current->content);
//         current = current->next;
//     }

//     // Free the allocated memory for the nodes
//     free(node1);
//     free(node2);

//     return 0;
// }

// #include <stdlib.h>
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