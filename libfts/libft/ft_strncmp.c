/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 06:54:39 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:48:09 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned const char	*us1;
	unsigned const char	*us2;

	i = 0;
	us1 = (unsigned const char *)s1;
	us2 = (unsigned const char *)s2;
	while (i < n && (us1[i] != '\0' || us2[i] != '\0'))
	{
		if (us1[i] != us2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int ft_strncmp(const char *s1, const char *s2, size_t n);

// int main() {
//     const char *str1 = "He";
//     const char *str2 = "Hello";
//     size_t n = 0;

//     int result = ft_strncmp(str1, str2, -127-1);
// 	int result2 = strncmp(str1, str2, -127-1);
// 	printf("ft: %d\n", result);
// 	printf("real: %d\n", result2);

//     // if (result < 0) {
//     //     printf("'%s' is less than '%s' by %d\n", str1, str2, result);
//     // } else if (result > 0) {
//     //     printf("'%s' is greater than '%s' by %d\n", str1, str2, result);
//     // } else {
//     //     printf("'%s' is equal to '%s' by %d\n", str1, str2, result);
//     // }

//     return 0;
// }