/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:21:54 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:26 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst -> next == NULL)
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

// #include <stdio.h>
// int main() {
//     // Create a list with three nodes
//     t_list *node1 = (t_list *)malloc(sizeof(t_list));
//     t_list *node2 = (t_list *)malloc(sizeof(t_list));
//     t_list *node3 = (t_list *)malloc(sizeof(t_list));

//     if (node1 == NULL || node2 == NULL || node3 == NULL) {
//         printf("Failed to allocate memory for nodes.\n");
//         return 1;
//     }

//     node1->content = "Node 1";
//     node2->content = "Node 2";
//     node3->content = "Node 3";

//     node1->next = node2;
//     node2->next = node3;
//     node3->next = NULL;

//     // Find the last node in the list
//     t_list *lastNode = ft_lstlast(node1);

//     if (lastNode != NULL) {
//         // Print the content of the last node
//         printf("Last Node Content: %s\n", (char *)lastNode->content);
//     } else {
//         printf("List is empty.\n");
//     }

//     // Free the allocated memory for the nodes
//     free(node1);
//     free(node2);
//     free(node3);

//     return 0;
// }

// #include <stdlib.h>

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }				t_list;