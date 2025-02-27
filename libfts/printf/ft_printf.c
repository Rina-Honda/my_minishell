/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:36:11 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:51:15 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_output_conversion(va_list *ap, int sp)
{
	int	byte;

	byte = 0;
	if (sp == 0)
		byte = ft_print_c(ap);
	else if (sp == 1)
		byte = ft_print_s(ap);
	else if (sp == 2)
		byte = ft_print_p(ap);
	else if (sp == 3 || sp == 4 || sp == 5 || sp == 6 || sp == 7)
		byte = ft_print_idux(ap, sp);
	else
		byte = ft_print_percent();
	if (byte == -1)
		return (-1);
	return (byte);
}

static int	ft_serach_conversion(const char *format, va_list *ap)
{
	int	specifier;
	int	byte;

	specifier = -1;
	format++;
	specifier = ft_strchr_printf("cspdiuxX%", *format);
	if (specifier == -1)
		return (-1);
	byte = ft_output_conversion(ap, specifier);
	return (byte);
}

static int	ft_loop_format(const char *s, va_list *ap)
{
	int	temp;
	int	byte;

	byte = 0;
	while (*s != '\0')
	{
		if (*s == '%')
		{
			temp = ft_serach_conversion(s, ap);
			if (temp != -1)
				s++;
			else
				byte++;
			byte += temp - 1;
		}
		else
			write(1, s, 1);
		byte++;
		s++;
	}
	return (byte);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	const char	*s = format;
	int			byte;

	byte = 0;
	va_start(ap, format);
	if (format == NULL)
		return (-1);
	byte = ft_loop_format(s, &ap);
	va_end(ap);
	return (byte);
}

// #include <limits.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int result;
//     // int p = LONG_MAX;
//     // result = printf("%p\n", (void *)&p);
//     // printf("result: %d\n", result);
//     // result = ft_printf("%p\n", (void *)&p);
//     // ft_printf("result: %d\n", result);

//     // long p = ;
//     result = printf("%c\n");
//     printf("result1: %d\n", result);

//     result = ft_printf("%c\n");
//     printf("result2: %d\n", result);

// 	// int re = ft_strchr("cspdiuxX%", 'd');
// 	// printf("re = %d\n", re);
// 	return (0);
// }