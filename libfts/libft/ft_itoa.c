/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:28:48 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:46:03 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	count_digit(long num)
{
	size_t	count;

	count = 1;
	if (num < 0)
	{
		num *= -1;
		count++;
	}
	while (num >= 10)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static char	*make_array(long num, size_t len, char *p)
{
	p[len] = '\0';
	if (num == 0)
		p[0] = '0';
	while (num != 0)
	{
		len--;
		if (num >= 10)
			p[len] = '0' + num % 10;
		else
			p[len] = '0' + num;
		num = num / 10;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	long	num;
	size_t	len;
	char	*p;

	num = n;
	len = count_digit(num);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	if (n < 0)
	{
		num *= -1;
		p[0] = '-';
	}
	return (make_array(num, len, p));
}

// #include <stdio.h>

// int main(void)
// {
//     int num = -620;
//     char *result = ft_itoa(num);

//     if (result == NULL)
//     {
//         printf("Memory allocation failed.\n");
//         return 1;
//     }

//     printf("Integer as a string: %s\n", result);

//     free(result);

//     return 0;
// }

// int main(void)
// {
// 	int i;
// 	int answer;

// 	i = -620;
// 	answer = count_digit(i);
// 	printf("%d", answer);
// 	return 0;
// }