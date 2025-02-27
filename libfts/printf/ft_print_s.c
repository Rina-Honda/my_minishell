/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 23:21:04 by rhonda            #+#    #+#             */
/*   Updated: 2023/12/15 23:21:04 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_put_str(char *s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	ft_print_s(va_list *ap)
{
	char	*s;
	int		len;

	s = (char *)va_arg(*ap, char *);
	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	ft_put_str(s, len);
	return (len);
}
