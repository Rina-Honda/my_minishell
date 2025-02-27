/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:15:13 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:30 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*p;

	len = ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

// #include "libft.h"
// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     const char *str = "kjhytgajekuy";

// // Copy the string using the strdup function.
//     char *strdup_result = strdup(str);

//     if (strdup_result == NULL)
//     {
//         printf("strdup failed\n");
//         return 1;
//     }

// // Copy the string using the ft_strdup function.
//     char *ft_strdup_result = ft_strdup(str);

//     if (ft_strdup_result == NULL)
//     {
//         printf("ft_strdup failed\n");
//         free(strdup_result); //free the strdup result if ft_strdup fails.
//         return 1;
//     }

//     printf("Original string: %s\n", str);
//     printf("strdup result: %s\n", strdup_result);
//     printf("ft_strdup result: %s\n", ft_strdup_result);

//     if (strcmp(strdup_result, ft_strdup_result) == 0)
//     {
//         printf("Results match!\n");
//     }
//     else
//     {
//         printf("Results do not match.\n");
//     }

//     free(strdup_result);
//     free(ft_strdup_result);

//     return 0;
// }