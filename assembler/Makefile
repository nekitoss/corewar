# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/08 19:01:12 by yrobotko          #+#    #+#              #
#    Updated: 2017/10/23 18:46:26 by yrobotko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../asm

G = gcc

FLAGS = -Wall -Wextra -Werror

SRC =   asm.c \
		asm0.c \
		asm1.c \
		asm2.c \
		asm3.c \
		asm4.c \
		asm5.c \
		asm6.c \
		asm7.c \
		asm8.c \
		asm9.c \
		asm10.c \
		asm11.c \
		asm12.c \
		asm13.c \

OBJ = $(SRC:.c=.o)

DEL = rm -f

LIB = libft/libft.a

all: $(NAME)

$(NAME) : $(OBJ)
	make -C ./libft/ re
	gcc $(FLAG) $(LIB) $(OBJ) -o $(NAME) 
%.o: %.c
	$(G) $(FLAGS) -c -o $@ $<
clean:
	$(DEL) $(OBJ)
	$(DEL) libft/*.o
fclean: clean
	$(DEL) $(NAME)
	$(DEL) libft.a
	$(DEL) libft/libft.a
re:	fclean all

