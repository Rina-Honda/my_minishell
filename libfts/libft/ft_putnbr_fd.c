/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:36:08 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:14 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = (long)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	if (num >= 10)
	{
		ft_putnbr_fd((num / 10), fd);
	}
	ft_putchar_fd(num % 10 + '0', fd);
}

// #include <stdio.h>
// int main(void)
// {
//     int number = 0;
//     int file_descriptor = 1;
// 		ft_putnbr_fd(number, file_descriptor);
//     printf("\nOutput using printf: %d\n", number);

//     return 0;
// }