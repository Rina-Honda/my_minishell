/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:47:23 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 22:44:19 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	ft_getchar(int fd)
{
	static t_buffinfo	buffinfo[OPEN_MAX];
	char				c;

	if (buffinfo[fd].read_byte == 0)
	{
		buffinfo[fd].read_byte = read(fd, buffinfo[fd].buff, BUFFER_SIZE);
		if (buffinfo[fd].read_byte <= 0)
		{
			ft_memset(buffinfo[fd].buff, 0, BUFFER_SIZE);
			buffinfo[fd].read_byte = 0;
			return (EOF);
		}
		buffinfo[fd].buffptr = buffinfo[fd].buff;
	}
	buffinfo[fd].read_byte--;
	c = *(buffinfo[fd].buffptr++);
	return (c);
}

static char	*ft_appendchar(t_line *line, char c)
{
	char	*new_str;

	if (line->length + 1 >= line->capacity)
	{
		if (!line->capacity)
			line->capacity = 2;
		else
			line->capacity *= 2;
		new_str = (char *)malloc(sizeof(char) * line->capacity);
		if (!new_str)
			return (NULL);
		if (line->string)
		{
			ft_memcpy(new_str, line->string, line->length);
			free(line->string);
		}
		line->string = new_str;
	}
	line->string[line->length] = c;
	line->length++;
	line->string[line->length] = '\0';
	return (line->string);
}

char	*get_next_line(int fd)
{
	t_line	result;
	char	c;

	if (fd < 0 || OPEN_MAX <= fd)
		return (NULL);
	result.string = NULL;
	result.length = 0;
	result.capacity = 0;
	while (1)
	{
		c = ft_getchar(fd);
		if (c == EOF)
			break ;
		if (!ft_appendchar(&result, c))
		{
			free(result.string);
			return (NULL);
		}
		if (c == '\n')
			break ;
	}
	if (result.length > 0)
		return (result.string);
	free(result.string);
	return (NULL);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(void){
//     int fd = open("example.txt", O_RDONLY);
// 	char    *line = NULL;

//     if(fd < 0)
//         return -1;
//     while(1)
//     {
//         line = get_next_line(fd);
// 		if(!line)
// 			break;
//         printf("%s", line);
//         free(line);

//     }
//     close(fd);
// 	return 0;
// }

// int main(void)
// {
//     int fd1, fd2, fd3;
//     char *line1, *line2, *line3;
//     int active_fd1, active_fd2, active_fd3;

//     fd1 = open("file1.txt", O_RDONLY);
//     if (fd1 < 0)
//     {
//         perror("Error opening file1.txt");
//         return 1;
//     }

//     fd2 = open("file2.txt", O_RDONLY);
//     if (fd2 < 0)
//     {
//         perror("Error opening file2.txt");
//         close(fd1);
//         return 1;
//     }

//     fd3 = open("file3.txt", O_RDONLY);
//     if (fd3 < 0)
//     {
//         perror("Error opening file3.txt");
//         close(fd1);
//         close(fd2);
//         return 1;
//     }

//     active_fd1 = active_fd2 = active_fd3 = 1;

//     while (active_fd1 || active_fd2 || active_fd3)
//     {
//         if (active_fd1)
//         {
//             line1 = get_next_line(fd1);
//             if (line1)
//             {
//                 printf("File1: %s", line1);
//                 free(line1);
//             }
//             else
//             {
//                 active_fd1 = 0;
//             }
//         }

//         if (active_fd2)
//         {
//             line2 = get_next_line(fd2);
//             if (line2)
//             {
//                 printf("File2: %s", line2);
//                 free(line2);
//             }
//             else
//             {
//                 active_fd2 = 0;
//             }
//         }

//         if (active_fd3)
//         {
//             line3 = get_next_line(fd3);
//             if (line3)
//             {
//                 printf("File3: %s", line3);
//                 free(line3);
//             }
//             else
//             {
//                 active_fd3 = 0;
//             }
//         }
//     }

//     close(fd1);
//     close(fd2);
//     close(fd3);

//     return 0;
// }