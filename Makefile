# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbagdon <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/18 23:42:22 by cbagdon           #+#    #+#              #
#    Updated: 2019/02/23 15:27:24 by cbagdon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRCS = array.c \
	   main.c \
	   validate.c \
	   board.c \
	   tetriminos.c \
	   op.c

OBJECTS = $(patsubst %.c,%.o,$(SRCS))

all: $(NAME)

$(NAME):
		make -C libft
		gcc -Wall -Wextra -Werror -c $(SRCS) -I includes/fillit.h
		gcc -Wall -Wextra -Werror -o $(NAME) $(OBJECTS) -L ./libft/ -lft

clean:
		make -C libft clean
		rm -rf $(OBJECTS)

fclean: clean
		make -C libft fclean
		rm -rf $(NAME)

re: fclean all
