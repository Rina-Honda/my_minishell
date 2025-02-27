/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:32:01 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:44:42 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (count > 0 && SIZE_MAX / count < size)
		return (NULL);
	p = (void *)malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

// #include <stdio.h>
// #include <limits.h>
// #include "libft.h"

// int main() {
//     size_t count = 5; // Number of elements: 5
//     // size_t size = sizeof(int); // Size of each element: int
//     // int *arr = (int *)ft_calloc(INT_MIN, INT_MIN);
// 	int *arrc = (int *)calloc(INT_MIN, INT_MIN);

//     // if (arr == NULL) {
//     //     printf("ft: Memory allocation failed\n");
//     //     return 1;
//     // }

//     // // Verify that the allocated memory is initialized to zero
//     // for (size_t i = 0; i < count; i++) {
//     //     printf("%d, ", arr[i]); // Should print zeros
//     // }

//     // // Free the allocated memory
//     // free(arr);

//  if (arrc == NULL) {
//         printf("ca: Memory allocation failed\n");
//         return 1;
//     }

//     // Verify that the allocated memory is initialized to zero
//     for (size_t i = 0; i < count; i++) {
//         printf("%d, ", arrc[i]); // Should print zeros
//     }

//     // Free the allocated memory
//     free(arrc);
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main() {
//     // test1
//     size_t count = 10;
//     size_t size = 4;
// 	void *ptr0 = calloc(count, size);
// 	if (*(char *)ptr0 == '\0')
// 		printf("ptr0 is null\n");
// 	printf("ptr0: %p\n", ptr0);
// 	printf("ptr0: %c\n", *(char *)ptr0);
// 	free (ptr0);
//     return 0;
// }