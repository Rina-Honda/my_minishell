/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:32:53 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:45:36 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// #include <limits.h>

// int ft_isascii(int c);

// int main(void)
// {
//     int test_cases[20] = {0, 1, 127, 128, 255, -1, -128, -129, 'a', 'A',
//                           'z', 'Z', '0', '9', '!', '{', '}', '~',
//                            INT_MAX, INT_MIN};
//     int expected_results[20] = {1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
//                                 1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
//     int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

//     for (int i = 0; i < num_test_cases; i++)
//     {
//         int result = ft_isascii(test_cases[i]);
//         int expected = expected_results[i];
//         if (result == expected)
//         {
//             printf("Test case %d passed\n", i + 1);
//         }
//         else
//         {
//             printf("Test case %d failed: expected %d but got %d\n",
//                    i + 1, expected, result);
//         }
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <ctype.h>

// int main() {
//     int ch1 = 'A';  // ASCII character 'A'
//     int ch2 = 128;  // Non-ASCII character

//     printf("%c is %s an ASCII\n", ch1, (isascii(ch1) ? "" : "not"));
//     printf("%c is %s an ASCII (ft)\n", ch1, (ft_isascii(ch1) ? "" : "not"));
//     printf("%c is %s an ASCII \n", ch2, (isascii(ch2) ? "" : "not"));
//     printf("%c is %s an ASCII (ft)\n", ch2, (ft_isascii(ch2) ? "" : "not"));
//     return 0;
// }