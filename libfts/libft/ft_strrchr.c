/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 06:35:41 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:48:17 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			len;
	unsigned char	uc;

	len = ft_strlen(s);
	uc = (unsigned char)c;
	while (len > 0)
	{
		if (s[len] == uc)
			return ((char *)(s + len));
		len--;
	}
	if (s[0] == uc)
		return ((char *)s);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main() {
//     const char *str = "libft-test-tokyo";
//     char searchChar = 'z';

//     char *result = strrchr(str, searchChar);
// 	char *result2 = ft_strrchr(str, searchChar);

//     if (result != result2) {
// 		printf("ft_strrchr does not work correctly.\n");
// 		printf("'%c' found at: %ld\n", searchChar, result - str + 1);
// 		printf("'%c' found at: %ld\n", searchChar, result2 - str + 1);
//         // printf("'%c' found at: %ld\n", searchChar, result - str + 1);
//     } else {
// 		printf("ft_strrchr works correctly.\n");
//         // printf("'%c' not found in the string.\n", searchChar);
//     }

//     return 0;
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }