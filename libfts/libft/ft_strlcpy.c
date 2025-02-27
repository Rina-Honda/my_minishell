/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 02:31:27 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:56 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dst == NULL || dstsize == 0)
		return (src_len);
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

// #include <stdio.h>
// #include <stddef.h>
// #include <string.h>

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// int main() {
//     // Test string
//     const char *source = "Hello";
//     char destination[3]; // Buffer size for copying
//     // Get the length of the original string using ft_strlen
//     size_t len = ft_strlen(source);
//     // Copy the string safely using ft_strlcpy
//     size_t copied = ft_strlcpy(destination, source, 0);
// 	size_t au_copied = strlcpy(destination, source, 0);
//     // Display the results
//     printf("Length of the original string: %zu\n", len);
//     printf("Copied string: %s\n", destination);
//     printf("Number of characters tried to copy: %zu\n", copied);
// 	printf("Number of characters tried to copy: %zu\n", au_copied);
//     return 0;
// }
