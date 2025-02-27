/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 23:24:56 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:52 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*q;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	p = (unsigned char *)dst;
	q = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		p[i] = q[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     char source[] = "Hello, World!";
//     char destination1[20];
//     char destination2[20];

//     // Copy using custom ft_memcpy function
//     ft_memcpy(destination1, source, strlen(source) + 1);

//     // Copy using standard memcpy function
//     memcpy(destination2, source, strlen(source) + 1);

//     // Compare the results after copying
//     if (strcmp(destination1, destination2) == 0) {
//         printf("Both functions produced the same result.\n");
//     } else {
//         printf("Functions produced different results.\n");
//     }

//     return 0;
// }