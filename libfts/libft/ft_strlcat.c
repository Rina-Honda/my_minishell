/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 04:29:44 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:45 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	i = 0;
	while (dstlen + i < dstsize - 1 && src[i] != '\0')
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

// #include <stdio.h>
// #include <stddef.h>

// int main() {
//     char destination[15] = "sd";
//     const char *source = "World!";
//     size_t dstlen = ft_strlen(destination);
//     size_t concat = ft_strlcat(destination, source, sizeof(destination));
//     printf("Destination string: %s\n", destination);
//     printf("Length of the destination string: %zu\n", dstlen);
//     printf("Total length (return value): %zu\n", concat);
//     return 0;
// }

// #include <stdio.h>
// #include <stddef.h>

// int main() {

//     char *src1 = calloc(100, sizeof(char));
// 	char *src2 = calloc(100, sizeof(char));
// 	for (int i = 0; i < 99; i++)
// 	{
// 		src1[i] = i + 1;
// 		src2[i] = i + 1;
// 	}

// 	char *src3 = calloc(5, sizeof(char));
// 	char *src4 = calloc(5, sizeof(char));
//     size_t ft_concat = ft_strlcat(src1, src3, 10);
// 	size_t re_concat = ft_strlcat(src2, src4, 10);
//     printf("Total length (return value ft): %zu\n", ft_concat);
// 	printf("Total length (return value real): %zu\n", re_concat);
// 	free(src1);
// 	free(src2);
// 	free(src3);
// 	free(src4);
//     return 0;
// }

// #include <stdio.h>
// #include <stddef.h>

// int main() {
//     char b[0xF] = "nyan !";

//     const char *source = "World!";
//     size_t dstlen = ft_strlen(b);
//     size_t concat = ft_strlcat(((void *)0), b, 2);
//     printf("Destination string: %s\n", b);
//     printf("Length of the destination string: %zu\n", dstlen);
//     printf("Total length (return value): %zu\n", concat);
//     return 0;
// }
