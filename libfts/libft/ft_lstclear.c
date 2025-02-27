/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:24:19 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:14 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (del == NULL || lst == NULL || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

// // Custom deletion function for testing
// void	del_content(void *content)
// {
// 	free(content);
// }

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	// Initialize the list
// 	t_list *list = ft_lstnew(strdup("Item 1"));
// 	list->next = ft_lstnew(strdup("Item 2"));
// 	list->next->next = ft_lstnew(strdup("Item 3"));

// 	// Display the content of the list
// 	t_list *current = list;
// 	while (current != NULL)
// 	{
// 		printf("current: %s\n", (char *)current->content);
// 		current = current->next;
// 	}

// 	// Clear the list
// 	ft_lstclear(&list, del_content);

// 	if (list == NULL)
// 		printf("List is empty.\n");

// 	return (0);
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

// void	ft_lstdelone(t_list *lst, void (*del)(void *))
// {
// 	if (lst == NULL || del == NULL)
// 		return ;
// 	del(lst -> content);
// 	free(lst);
// }