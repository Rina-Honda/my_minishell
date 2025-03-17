/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:06:31 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 22:08:33 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == s2)
		return (0);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}
