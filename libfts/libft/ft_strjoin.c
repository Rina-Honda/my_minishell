/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:48:50 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:38 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}

// #include <stdio.h>

// int main()
// {
//     const char *str1 = "Hello, ";
//     const char *str2 = "World!";
//     char *result = ft_strjoin(str1, str2);

//     if (result == NULL)
//     {
//         printf("ft_strjoin failed\n");
//         return 1;
//     }
//     printf("String 1: %s\n", str1);
//     printf("String 2: %s\n", str2);
//     printf("Concatenated String: %s\n", result);
//     free(result);
//     return 0;
// }