/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:52:14 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:30 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_lst;
	void	*new_content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		new_content = f(lst -> content);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst -> next;
	}
	return (new_lst);
}

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

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	if (del == NULL || lst == NULL || *lst == NULL)
// 		return ;
// 	while (*lst != NULL)
// 	{
// 		ft_lstdelone(*lst, del);
// 		*lst = (*lst)-> next;
// 	}
// }

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

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*last;

// 	if (new == NULL)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	else
// 	{
// 		last = ft_lstlast(*lst);
// 		last -> next = new;
// 	}
// }