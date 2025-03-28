/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 00:39:38 by rhonda            #+#    #+#             */
/*   Updated: 2023/12/16 00:39:38 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_putnbr_pointer(uintptr_t n, int fd)
{
	char	*str;
	int		byte;

	byte = 0;
	str = "0123456789abcdef";
	if (n >= 16)
		byte += ft_putnbr_pointer(n / 16, fd);
	write(fd, &str[n % 16], 1);
	byte++;
	return (byte);
}

int	ft_dprint_p(va_list *ap, int fd)
{
	void			*p;
	int				len;

	p = va_arg(*ap, void *);
	write(fd, "0x", 2);
	len = ft_putnbr_pointer((uintptr_t)p, fd) + 2;
	return (len);
}
