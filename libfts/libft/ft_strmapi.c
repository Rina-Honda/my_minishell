/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:17:21 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:48:05 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	p = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}

// #include <stdio.h>

// char custom_function(unsigned int index, char c)
// {
//     // function example
//     return c + index;
// }

// int main(void)
// {
//     char input[] = "Hello, World!";
//     char *result = ft_strmapi(input, custom_function);

//     if (result == NULL)
//     {
//         printf("Memory allocation failed.\n");
//         return 1;
//     }

//     printf("Original string: %s\n", input);
//     printf("Modified string: %s\n", result);

//     free(result);

//     return 0;
// }