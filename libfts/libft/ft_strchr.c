/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 06:02:17 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:26 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == uc)
			return ((char *)(s + i));
		i++;
	}
	if (uc == '\0')
		return ((char *)(s + i));
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main() {
//     const char *str = "Hello, World!";
//     char searchChar = 'H';

//     char *result = ft_strchr(str, searchChar);

//     if (result != NULL) {
//         printf("'%c' found at: %ld\n", searchChar, result - str + 1);
//     } else {
//         printf("'%c' not found in the string.\n", searchChar);
//     }

//     return 0;
// }