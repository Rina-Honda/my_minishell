/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:06:01 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:48:21 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*p;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	if (*s1 == '\0')
		end = 0;
	else
		end = ft_strlen(s1) - 1;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (start < end && ft_strchr(set, s1[end]) != NULL)
		end--;
	len = end - start + 1;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, &s1[start], len + 1);
	return (p);
}

// #include <stdio.h>

// int main()
// {
//     const char *input_str = "  \t\n";
//     const char *trim_set = " \t";

//     char *trimmed_str = ft_strtrim(input_str, trim_set);

//     if (trimmed_str == NULL)
//     {
//         printf("NULL returned\n");
//         return 1;
//     }

//     printf("Original string: \"%s\"\n", input_str);
//     printf("Trimmed string: \"%s\"\n", trimmed_str);

//     free(trimmed_str);

//     return 0;
// }