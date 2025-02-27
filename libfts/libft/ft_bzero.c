/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:54:33 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:44:38 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char		*p;
	size_t				i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*p = 0;
		p++;
		i++;
	}
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char test_string[] = "Hello, World!";
// 	printf("String: %s\n", test_string);
//     size_t test_length = strlen(test_string);
//     ft_bzero(test_string, test_length);
//     printf("Cleared String: %s\n", test_string);
//     return 0;
// }