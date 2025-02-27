/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:15:54 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:45:51 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int main() {
//     char input_char;
//     printf("Please enter a string to test: ");
//     // Repeat until a newline character (Enter key) is entered
//     while (1) {
//         scanf(" %c", &input_char); // Use space to skip leading white spaces
//         // Exit the loop when a newline character (Enter key) is entered
//         if (input_char == '\n') {
//             break;
//         }
//         // Test with the custom ft_isdigit function
//         if (ft_isdigit(input_char)) {
//             printf("\"%c\" is a digit (ft_isdigit)\n", input_char);
//         } else {
//             printf("\"%c\" is not a digit (ft_isdigit)\n", input_char);
//         }
//         // Test with the standard library's isdigit function
//         if (isdigit(input_char)) {
//             printf("\"%c\" is a digit (isdigit function)\n", input_char);
//         } else {
//             printf("\"%c\" is not a digit (isdigit function)\n", input_char);
//         }
//     }
//     return 0;
// }