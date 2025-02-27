/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:13:28 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:48:00 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// #include <string.h> // Using standard strlen function for validation
// #include <stdio.h>

// int main() {
//     const char *str = "Hello, World!"; // The string to be tested
//     // Using ft_strlen to get the length of the string
//     size_t len = ft_strlen(str);
//     // Displaying the result of ft_strlen
//     printf("Result from ft_strlen: %zu\n", len);
//     // Using standard strlen function for validation
//     size_t correct_len = strlen(str);
//     printf("Correct result (from strlen): %zu\n", correct_len);
//     // Checking if the results match
//     if (len == correct_len) {
//         printf("ft_strlen works correctly.\n");
//     } else {
//         printf("ft_strlen does not work correctly.\n");
//     }
//     return 0;
// }