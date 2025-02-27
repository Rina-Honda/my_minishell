/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:42:20 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:22 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}

// #include <stdio.h>
// void    print_content(void *content)
// {
//     printf("%s\n", (char *)content);
// }

// int main() {
//     // Create list nodes
//     t_list *node1 = ft_lstnew("Node 1");
//     t_list *node2 = ft_lstnew("Node 2");
//     t_list *node3 = ft_lstnew("Node 3");

//     // Connect the nodes to form a list
//     node1->next = node2;
//     node2->next = node3;

//     // Apply the print_content function to the content of each node
//     ft_lstiter(node1, print_content);

//     // Free memory
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