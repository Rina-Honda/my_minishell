/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:24:41 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:47:22 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	free_array(char **array, size_t i)
{
	while (i > 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

static int	cnt_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != '\0' && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	cnt_words(const char *s, char c)
{
	size_t		count;
	const char	*start;

	count = 0;
	start = s;
	while (*s != '\0')
	{
		if (*s != c && (*(s - 1) == c || s == start))
			count++;
		s++;
	}
	return (count);
}

static char	**make_null(void)
{
	char	**array;

	array = (char **)malloc(sizeof(char *));
	if (array == NULL)
		return (NULL);
	array[0] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;

	if (s == NULL || s[0] == '\0')
		return (make_null());
	array = (char **)malloc(sizeof(char *) * (cnt_words(s, c) + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		array[i++] = ft_substr(s, 0, cnt_word_len(s, c));
		if (array[i - 1] == NULL)
		{
			free_array(array, i - 1);
			return (NULL);
		}
		s += cnt_word_len(s, c);
	}
	array[i] = NULL;
	return (array);
}

// int main(){
// 	char **splitted;
// 	int i;

// 	splitted = ft_split("tripouille", 0);
// 	i = 0;
// 	while(i < 2)
// 	{
// 		printf("result:%s\n", splitted[i]);
// 		i++;
// 	}
// }

// #include <stdio.h>
// int main(void)
// {
//     // char const *s = "    This    is a    sample string   to split   ";
//     char const *s = "--32----45666--2235";
//     char c = '-';
//     char **result = ft_split(s, c);

//     if (result == NULL)
//     {
//         printf("Memory allocation failed.\n");
//         return (1);
//     }

// 	if (*result == '\0')
// 	{
// 		printf("result is null\n");
// 		return (1);
// 	}

//     int i = 0;
//     while (result[i] != NULL)
//     {
//         printf("Element %d: %s\n", i, result[i]);
//         free(result[i]);
//         i++;
//     }

//     free(result);
//     return (0);
// }

// #include <stdio.h>
// int main(void)
// {
// 	char const *s = "    This    is a    sample string   to split   ";
// 	char c = ' ';

// 	int element = cnt_words(s, c);
// 	printf("element: %d\n", element);
// 	return (0);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	size_t	max_len;
// 	char	*p;

// 	if (s == NULL)
// 		return (NULL);
// 	max_len = ft_strlen(s);
// 	if (max_len < len)
// 		len = max_len;
// 	p = (char *)malloc(sizeof(char) * (len + 1));
// 	if (p == NULL)
// 		return (NULL);
// 	else if (max_len <= start || len == 0)
// 	{
// 		*p = '\0';
// 		return (p);
// 	}
// 	i = 0;
// 	while (i < len && s[start + i] != '\0')
// 	{
// 		p[i] = s[start + i];
// 		i++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }