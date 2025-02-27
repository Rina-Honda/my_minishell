/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 07:33:13 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:43 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	uc;

	i = 0;
	p = (unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (p[i] == uc)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main() {
//     const char *str = "Hello, World!";
//     char target = 'l';
// 	char s[] = {0, 1, 2 ,3 ,4 ,5};

//     const void *result = ft_memchr(str, target, strlen(str) + 10);
// 	const void *result2 = ft_memchr(s, 2 + 256, 3);

//     if (result != NULL) {
//         printf("'%c' found at: %ld\n", target, (char *)result - str + 1);
//     } else {
//         printf("'%c' not found in the string.\n", target);
//     }

//     return 0;
// }