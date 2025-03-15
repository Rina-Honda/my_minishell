# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 23:22:26 by rhonda            #+#    #+#              #
#    Updated: 2025/03/15 18:17:53 by rhonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libfts
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/main.c \
	src/tokenize.c \
	src/parse.c \
	src/expand.c \
	src/redirect.c \
	src/pipe.c \
	src/exec.c \
	src/signal.c \
	src/env.c \
	src/map.c \
	src/builtin.c \
	src/builtin_exit.c \
	src/builtin_export.c \
	src/builtin_unset.c \
	src/builtin_env.c \
	src/builtin_cd.c \
	src/builtin_echo.c \
	src/builtin_pwd.c \
	src/util.c \
	src/error.c \
	src/free.c \

OBJS = $(SRCS:.c=.o) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
