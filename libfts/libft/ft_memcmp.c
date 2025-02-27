/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:09:10 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:48 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;
	size_t			i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p[i] != q[i])
			return (p[i] - q[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include "libft.h"

// int ft_memcmp(const void *s1, const void *s2, size_t n);

// int main() {
//     char str1[] = "";
//     char str2[] = "\0";
//     size_t n = 5;

//     int result = ft_memcmp(str1, str2, n);

//     if (result < 0) {
//         printf("str1 is less than str2\n");
//     } else if (result > 0) {
//         printf("str1 is greater than str2\n");
//     } else {
//         printf("str1 is equal to str2\n");
//     }

//     return 0;
// }