/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:36:45 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:45:58 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isprint(int c)
{
	if (' ' <= c && c <= '~')
		return (1);
	return (0);
}

// #include <stdio.h>

// // Declaration of ft_isprint function
// int ft_isprint(int c);

// int main() {
//     // Test cases with various characters
//     char printableChars[] = "Hello, World! 123"; // printable characters
//     char nonPrintableChars[] = "\n\t\x07\x01";  // non-printable characters
//     printf("Testing ft_isprint function:\n");
//     // Test printable characters
//     printf("Printable characters:\n");
//     for (int i = 0; printableChars[i] != '\0'; i++) {
//         if (ft_isprint(printableChars[i])) {
//             printf("'%c' is printable.\n", printableChars[i]);
//         } else {
//             printf("'%c' is not printable.\n", printableChars[i]);
//         }
//     }
//     // Test non-printable characters
//     printf("\nNon-printable characters:\n");
//     for (int i = 0; nonPrintableChars[i] != '\0'; i++) {
//         if (ft_isprint(nonPrintableChars[i])) {
//             printf("'%c' is printable.\n", nonPrintableChars[i]);
//         } else {
//             printf("'%c' is not printable.\n", nonPrintableChars[i]);
//         }
//     }
//     return 0;
// }