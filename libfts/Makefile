# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 21:30:06 by rhonda            #+#    #+#              #
#    Updated: 2025/02/05 22:58:54 by rhonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBFT = libft/ft_isalpha.c \
		libft/ft_isdigit.c \
		libft/ft_isalnum.c \
		libft/ft_isascii.c \
		libft/ft_isprint.c \
		libft/ft_strlen.c \
		libft/ft_memset.c \
		libft/ft_bzero.c \
		libft/ft_memcpy.c \
		libft/ft_memmove.c \
		libft/ft_strlcpy.c \
		libft/ft_strlcat.c \
		libft/ft_toupper.c \
		libft/ft_tolower.c \
		libft/ft_strchr.c \
		libft/ft_strrchr.c \
		libft/ft_strncmp.c \
		libft/ft_memchr.c \
		libft/ft_memcmp.c \
		libft/ft_strnstr.c \
		libft/ft_atoi.c \
		libft/ft_calloc.c \
		libft/ft_strdup.c \
		libft/ft_substr.c \
		libft/ft_strjoin.c \
		libft/ft_strtrim.c \
		libft/ft_split.c \
		libft/ft_itoa.c \
		libft/ft_strmapi.c \
		libft/ft_striteri.c \
		libft/ft_putchar_fd.c \
		libft/ft_putstr_fd.c \
		libft/ft_putendl_fd.c \
		libft/ft_putnbr_fd.c \
		libft/ft_lstnew.c \
		libft/ft_lstadd_front.c \
		libft/ft_lstsize.c \
		libft/ft_lstlast.c \
		libft/ft_lstadd_back.c

PRINTF = printf/ft_printf.c \
		printf/ft_print_c.c \
		printf/ft_print_s.c \
		printf/ft_print_idux.c \
		printf/ft_print_p.c \
		printf/ft_print_percent.c \
		printf/ft_strchr_printf.c

GNL = gnl/get_next_line.c \

SRCS = $(LIBFT) $(PRINTF) $(GNL)
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar rc $(NAME) $(OBJS)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
