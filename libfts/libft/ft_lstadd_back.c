/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:34:26 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:07 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast(*lst);
		last -> next = new;
	}
}

// #include <stdio.h>
// int main()
// {
//     // Initialize the list
//     t_list *list = NULL;

//     // Add elements to the list
//     t_list *elem1 = malloc(sizeof(t_list));
//     elem1->content = "Element 1";
//     elem1->next = NULL;
//     ft_lstadd_back(&list, elem1);

//     t_list *elem2 = malloc(sizeof(t_list));
//     elem2->content = "Element 2";
//     elem2->next = NULL;
//     ft_lstadd_back(&list, elem2);

//     // Display the contents of the list
//     t_list *current = list;
//     while (current != NULL)
//     {
//         printf("Content: %s\n", (char *)current->content);
//         current = current->next;
//     }

//     // Free memory
//     while (list != NULL)
//     {
//         t_list *temp = list;
//         list = list->next;
//         free(temp);
//     }

//     return 0;
// }

// #include <stdlib.h>

// typedef struct s_list
// {    
// 	void			*content;
// 	struct s_list	*next;
// }				t_list;

// t_list	*ft_lstlast(t_list *lst)
// {
// 	while (lst != NULL)
// 	{
// 		if (lst -> next == NULL)
// 			return (lst);
// 		lst = lst -> next;
// 	}
// 	return (lst);
// }