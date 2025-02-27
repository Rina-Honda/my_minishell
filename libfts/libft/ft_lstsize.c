/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:11:08 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:38 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
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

//     // Calculate the size of the list
//     int size = ft_lstsize(node1);

//     // Print the size of the list
//     printf("List size: %d\n", size);

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