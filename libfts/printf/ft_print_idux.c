/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_idux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:25:24 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:49:17 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_putnbr_base(long long n, int base, int specifier)
{
	char	*str;
	int		byte;

	byte = 0;
	str = "0123456789abcdefABCDEF";
	if (n < 0 && (specifier == 3 || specifier == 4))
	{
		write(1, "-", 1);
		byte++;
		n = -n;
	}
	if (n >= base)
		byte += ft_putnbr_base(n / base, base, specifier);
	if ((specifier == 7) && ((n % base) >= 10))
		write(1, &str[(n % base) + 6], 1);
	else
		write(1, &str[n % base], 1);
	byte++;
	return (byte);
}

int	ft_print_idux(va_list *ap, int specifier)
{
	long long	n;
	int			base;
	int			len;

	n = 0;
	base = 0;
	if (specifier == 3 || specifier == 4)
	{
		n = (int)va_arg(*ap, int);
		base = 10;
	}
	else if (specifier == 5)
	{
		n = (unsigned int)va_arg(*ap, unsigned int);
		base = 10;
	}
	else if (specifier == 6 || specifier == 7)
	{
		n = (unsigned int)va_arg(*ap, unsigned int);
		base = 16;
	}
	len = ft_putnbr_base(n, base, specifier);
	return (len);
}

// #include "ft_printf.h"

// int	ft_numlen_base(long long n, int base, int specifier)
// {
// 	int	len;

// 	len = 1;
// 	if (specifier == 2)
// 	{
// 		n = (uintptr_t)n;
// 		base = 10;
// 	}
// 	while (n >= (long long)base)
// 	{
// 		n /= base;
// 		len++;
// 	}
// 	return (len);
// }

// #include <stdio.h>
// int main(void)
// {
//     long long num1 = 123456;
//     int base1 = 10;
//     int specifier1 = 1;
//     int len1 = ft_numlen_base(num1, base1, specifier1);
//     printf("Length 1: %d\n", len1);

//     uintptr_t num2 = (uintptr_t)0x12345678;
//     int base2 = 16;
//     int specifier2 = 2;
//     int len2 = ft_numlen_base(num2, base2, specifier2);
//     printf("Length 2: %d\n", len2);

//     long long num3 = -98765;
//     int base3 = 8;
//     int specifier3 = 4;
//     int len3 = ft_numlen_base(num3, base3, specifier3);
//     printf("Length 3: %d\n", len3);

//     return 0;
// }