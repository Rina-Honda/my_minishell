/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:33:09 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:48:26 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	max_len;
	char	*p;

	if (s == NULL)
		return (NULL);
	max_len = ft_strlen(s);
	if (max_len < len)
		len = max_len;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	else if (max_len <= start || len == 0)
	{
		*p = '\0';
		return (p);
	}
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

// #include <stdio.h>
// #include <stdlib.h> // Include stdlib.h for the free function
// #include "libft.h"

// int main()
// {
//     const char *str = "Hello, World";
//     // unsigned int start = 6; // Start index of the substring
//     // size_t len = 10; // Maximum length of the substring

//     char *substr = ft_substr("tripouille", 2, 1000);

//     if (substr == NULL)
//     {
//         printf("ft_substr failed\n");
//         return 1;
//     }

//     printf("Original string: %s\n", str);
//     printf("Substring: %s\n", substr);
// 	char *ptr = substr;
// 	char c = *ptr;
// 	printf("ptr: %p\n", ptr);
// 	printf("c: %c\n", c);

//     // Free the allocated memory
//     free(substr);

//     return 0;
// }