/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:34:06 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:44:33 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check_overflow(long long num, int sign, char str)
{
	long long	max_div;
	long long	max_mod;
	long long	min_div;
	long long	min_mod;

	max_div = LONG_MAX / 10;
	max_mod = LONG_MAX % 10;
	min_div = (LONG_MIN / 10) * -1;
	min_mod = (LONG_MIN % 10) * -1;
	if (sign == 1
		&& (num > max_div || (num == max_div && (str - '0') > max_mod)))
		return (0);
	if (sign == -1
		&& (num > min_div || (num == min_div && (str - '0') > min_mod)))
		return (0);
	return (1);
}

static char	*front(const char *str, int *sign)
{
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return ((char *)str);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	str = front(str, &sign);
	while ('0' <= *str && *str <= '9')
	{
		if (check_overflow(num, sign, *str) == 0)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		num = (num * 10) + (*str - '0');
		str++;
	}
	return ((int)(num * sign));
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// // // int ft_atoi(const char *str);

// int main() {
//     const char *str = "   +100";
//     int expected = atoi(str);
//     int result = ft_atoi(str);

//     if (result == expected) {
//         printf("ft_atoi and atoi produced the same result: %d\n", result);
//     } else {
//         printf("ft_atoi and atoi produced different results.\n");
//         printf("ft_atoi result: %d\n", result);
//         printf("atoi result: %d\n", expected);
//     }

//     return 0;
// }

// #include <stdio.h>
// #include "libft.h"

// int main()
// {
//     const char *test_strings[] = {"10, 123", "-456",
//  "  789", "0", "42abc", "abc42", "  -123abc", "-2147483648"};
//     int expected[] = {10, 123, -456, 789, 0, 42, 0, -123, -2147483648};
//     size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

//     for (size_t i = 0; i < num_tests; i++)
//     {
//         const char *test_str = test_strings[i];
//         int expected = expected[i];

//         int custom_result = ft_atoi(test_str);

//         int standard_result = atoi(test_str);

//         if (custom_result == expected && 
// 				standard_result == expected)
//         {
//             printf("Test %zu: Match\n", i + 1);
//         }
//         else
//         {
//             printf("Test %zu: Mismatch\n", i + 1);
//         }
// 		printf("%d\n", custom_result);
// 		printf("%d\n", standard_result); 
// // naze int_min mo syuturyoku dekiruno ??
//     }
//     return 0;
// }
