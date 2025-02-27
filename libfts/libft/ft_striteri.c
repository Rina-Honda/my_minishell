/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:53:20 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:34 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// // example
// void to_uppercase(unsigned int index, char *ch)
// {
// 	(void)index;
//     if (*ch >= 'a' && *ch <= 'z')
//     {
//         *ch = *ch - 'a' + 'A';
//     }
// }

// int main(void)
// {
//     char input[] = "Hello, World!";

//     printf("Original string: %s\n", input);

//     ft_striteri(input, to_uppercase);

//     printf("Modified string: %s\n", input);

//     return 0;
// }