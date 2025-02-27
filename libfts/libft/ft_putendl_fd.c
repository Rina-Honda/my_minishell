/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:28:29 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:09 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

// #include <stdio.h>
// int main(void)
// {
//     char *message = "Hello, World!";
//     int file_descriptor = 1;

//     printf("Output using printf:\n");
//     printf("%s\n", message);

//     ft_putendl_fd(message, file_descriptor);

//     return 0;
// }