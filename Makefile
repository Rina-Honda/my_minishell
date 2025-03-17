# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 23:22:26 by rhonda            #+#    #+#              #
#    Updated: 2025/03/17 22:48:43 by rhonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libfts
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/main.c \
	src/tokenize/tokenize.c \
	src/parse/parse.c \
	src/expand/expand.c \
	src/redirect/redirect.c \
	src/pipe/pipe.c \
	src/exec/exec.c \
	src/signal/signal.c \
	src/environ/env.c \
	src/environ/map.c \
	src/builtin/builtin.c \
	src/builtin/builtin_exit.c \
	src/builtin/builtin_export.c \
	src/builtin/builtin_unset.c \
	src/builtin/builtin_env.c \
	src/builtin/builtin_cd.c \
	src/builtin/builtin_echo.c \
	src/builtin/builtin_pwd.c \
	src/util/util.c \
	src/util/util_strtol.c \
	src/util/util_strcmp.c \
	src/error/error.c \
	src/error/syntax_error.c \
	src/error/error_exit.c \
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
