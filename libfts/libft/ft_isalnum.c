/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:20:53 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:45:06 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')
		|| ('0' <= c && c <= '9'))
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>

// // // Function to check if a string is alphanumeric
// int isAlphaNumericString(const char *str) {
//     while (*str) {
//         if (!ft_isalnum(*str)) {
//             return 0; // Non-alphanumeric character found
//         }
//         str++;
//     }
//     return 1; // All characters are alphanumeric
// }

// int main() {
//     char input_string[100];
//     printf("Please enter a string to test: ");
//     scanf("%s", input_string);
//     if (isAlphaNumericString(input_string)) {
//         printf("\"%s\" alphanumeric characters only\n", input_string);
//     } else {
//         printf("\"%s\" contains non-alphanumeric\n", input_string);
//     }
//     return 0;
// }