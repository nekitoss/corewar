#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkurchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/01 20:22:50 by mkurchin          #+#    #+#              #
#    Updated: 2017/10/01 20:22:51 by mkurchin         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = corewar
LIB_NAME = libft.a
LIB_PATH = ./libft/
PRINTF_NAME = libftprintf.a
LIB = $(addprefix $(LIB_PATH), $(LIB_NAME))
CC = gcc
SRC =
FLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@make -C libft/
		@make -C ft_printf
		gcc $(FLAGS) $(OBJ) $(LIB) $(PRINTF) -o $(NAME)

clean:
		@make fclean -C libft/
		@make fclean -C ft_printf/
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all