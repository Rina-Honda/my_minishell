/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:45:05 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:48:13 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (haystack == NULL && len == 0)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (i + j < len && haystack[i + j] == needle[j])
			{
				if (needle[j + 1] == '\0')
					return ((char *)&haystack[i]);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
//     const char *haystack = "Hello, World!";
//     const char *needle = "Hello, World!";
//     // size_t len = strlen(haystack);

//     char *result1 = ft_strnstr(haystack, needle, -1);

//     char *result2 = strnstr(haystack, needle, -1);

//     if ((result1 == NULL && result2 == NULL)||
// 		(result1 && result2 && strcmp(result1, result2) == 0))
//     {
//         printf("result: Match\n");
//     }
//     else
//     {
//         printf("result: Missmatch\n");
// }

//     return (0);
// }

// int	main(void)
// {
// 	const char *haystack = "aaabcabcd";
// 	const char *needle = "aabc";
// 	// size_t len = strlen(haystack);

// 	char *result1 = ft_strnstr(haystack, needle, -1);
// 	printf("ft: %p\n", result1);

// 	char *result2 = strnstr(haystack, needle, -1);
// 	printf("orig: %p\n", result2);

// 	if ((result1 == NULL && result2 == NULL) || (result1 && result2
// 			&& strcmp(result1, result2) == 0))
// 	{
// 		printf("result: Match\n");
// 	}
// 	else
// 	{
// 		printf("result: Missmatch\n");
// 	}

// 	return (0);
// }

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	const char *haystack = "abbbcdefg";
// 	const char *needle = "bbc";
// 	// size_t len = strlen(haystack);

// 	char *result1 = ft_strnstr(haystack, needle, 20);
// 	printf("ft: %p\n", result1);

// 	char *result2 = strnstr(haystack, needle, 20);
// 	printf("orig: %p\n", result2);

// 	if ((result1 == NULL && result2 == NULL) || (result1 && result2
// 			&& strcmp(result1, result2) == 0))
// 	{
// 		printf("result: Match\n");
// 	}
// 	else
// 	{
// 		printf("result: Missmatch\n");
// 	}

// 	return (0);
// }