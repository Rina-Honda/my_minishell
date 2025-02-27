/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 01:45:24 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:56 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*p;
	const unsigned char	*q;

	if (dst == NULL && src == NULL)
		return (NULL);
	p = (unsigned char *)dst;
	q = (const unsigned char *)src;
	if (dst <= src && dst + len <= src + len)
		ft_memcpy(dst, src, len);
	else
	{
		while (len != 0)
		{
			len--;
			p[len] = q[len];
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     char source[] = "Hello, World!";
//     char destination1[20];
//     char destination2[20];

//     // Copy using custom ft_memmove function
//     ft_memmove(destination1, source, strlen(source) + 1);
// 	printf("ft_memmove: %s\n", destination1);

//     // Copy using standard memmove function
//     memmove(destination2, source, strlen(source) + 1);
// 	printf("memmove: %s\n", destination2);

//     // Compare the results after copying
//     if (strcmp(destination1, destination2) == 0) {
//         printf("Both functions produced the same result.\n");
//     } else {
//         printf("Functions produced different results.\n");
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// int main() {
//     char *source = malloc(100);
//     char *destination1 = malloc(100);
//     char *destination2 = malloc(100);

//     // Copy using custom ft_memmove function
//     ft_memmove(destination1, destination1 + 50, 50);
// 	printf("ft_memmove: %s\n", destination1);

//     // Copy using standard memmove function
//     memmove(destination2, destination2 + 21, 50);
// 	printf("memmove: %s\n", destination2);

//     // Compare the results after copying
//     if (strcmp(destination1, destination2) == 0) {
//         printf("Both functions produced the same result.\n");
//     } else {
//         printf("Functions produced different results.\n");
//     }
// 	free(source);
// 	free(destination1);
// 	free(destination2);

//     return 0;
// }