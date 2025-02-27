/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 05:44:55 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:48:35 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int main() {
//     char testChars[] = {'a', 'A', '5', '$', 'z', 'Z'};
//     int numTests = sizeof(testChars) / sizeof(testChars[0]);

//     printf("Test Results for toupper function:\n");

//     for (int i = 0; i < numTests; i++) {
//         char c = testChars[i];
//         int result = toupper(c);
//         int customResult = ft_toupper(c);

//         printf("Character: %c, Sta: %c, Cus: %c\n", c, result, customResult);

//         if (result != customResult) {
//             printf("Test failed for character: %c\n", c);
//         }
//     }

//     return 0;
// }