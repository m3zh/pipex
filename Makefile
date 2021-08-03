# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 17:28:02 by mlazzare          #+#    #+#              #
#    Updated: 2021/08/02 14:12:40 by mlazzare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc -g3
CFLAGS = -Wall -Wextra -Werror

INC = ./inc/pipex.h \

SRC = \
	./src/main.c \
	./src/pipex.c \
	./src/pipex_utils.c \
	./src/string_utils.c \
	./src/ft_splitpath.c \
	./src/free.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
