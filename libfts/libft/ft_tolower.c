/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 05:57:18 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:48:31 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (c - 'A' + 'a');
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int main() {
//     char testChars[] = {'a', 'A', '5', '$', 'f', 'L'};
//     int numTests = sizeof(testChars) / sizeof(testChars[0]);

//     printf("Test Results for toupper function:\n");

//     for (int i = 0; i < numTests; i++) {
//         char c = testChars[i];
//         int result = tolower(c);
//         int customResult = ft_tolower(c);

//         printf("Character: %c, Sta: %c, Cus: %c\n", c, result, customResult);

//         if (result != customResult) {
//             printf("Test failed for character: %c\n", c);
//         }
//     }

//     return 0;
// }