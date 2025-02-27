/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:49:10 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:00 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	uc;
	unsigned char	*p;
	size_t			i;

	uc = (unsigned char)c;
	p = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*p = uc;
		p++;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>

// // Declaration of ft_memset function
// void *ft_memset(void *b, int c, size_t len);

// int main() {
//     char buffer[20]; // Test memory block
//     size_t len = sizeof(buffer);
//     int value = 'A'; // Value to fill the memory block with
//     // Fill the memory block using ft_memset
//     ft_memset(buffer, value, len);
//     // Display the filled memory block
//     printf("Memory block after filling: ");
//     for (size_t i = 0; i < len; i++) {
//         printf("%c ", buffer[i]);
//     }
//     printf("\n");
//     // Compare memory blocks to check if ft_memset works correctly
//     char expected[20];
//     memset(expected, value, len); // Use standard memset
//     if (result == 0) {
//         printf("ft_memset works correctly.\n");
//     } else {
//         printf("ft_memset does not work correctly.\n");
//     }
//     return 0;
// }
