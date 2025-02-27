/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:47:44 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:45:21 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>

// int main() {
//     char input_string[100];
//     printf("Please enter a string to test: ");
//     scanf("%s", input_string);
//     int isAllAlpha = 1; // 1: All alphabetic, 0: Non-alphabetic are
//     for (int i = 0; input_string[i] != '\0'; i++) {
//         if (!ft_isalpha(input_string[i])) {
//             isAllAlpha = 0;
//             break;
//         }
//     }
//     if (isAllAlpha) {
//         printf("\"%s\" only alphabetic characters.\n", input_string);
//     } else {
//         printf("\"%s\" contains non-alphabetic characters.\n", input_string);
//     }
//     return 0;
// }