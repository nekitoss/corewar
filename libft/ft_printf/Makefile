#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhulam <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/25 17:28:09 by rhulam            #+#    #+#              #
#    Updated: 2017/03/16 13:45:55 by rhulam           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a
CC = gcc
LIB_PATH = ./../
LIB = ft_memset.o \
    ft_bzero.o \
    ft_memcpy.o \
    ft_memccpy.o \
    ft_memmove.o \
    ft_memchr.o \
    ft_memcmp.o \
    ft_strlen.o \
    ft_strdup.o \
    ft_strcpy.o \
    ft_strncpy.o \
    ft_strcat.o \
    ft_strncat.o \
    ft_strlcat.o \
    ft_strchr.o \
    ft_strrchr.o \
    ft_strstr.o \
    ft_strnstr.o \
    ft_strcmp.o \
    ft_strncmp.o \
    ft_atoi.o \
    ft_isalpha.o \
    ft_isdigit.o \
    ft_isalnum.o \
    ft_isascii.o \
    ft_isprint.o \
    ft_toupper.o \
    ft_tolower.o \
        ft_strtrim.o \
        ft_strsub.o \
        ft_strsplit.o \
        ft_strnew.o \
        ft_strmapi.o \
        ft_strmap.o \
        ft_strjoin.o \
        ft_striter.o \
        ft_striteri.o \
        ft_strequ.o \
        ft_strnequ.o \
        ft_strdel.o \
        ft_strclr.o \
        ft_putstr.o \
        ft_putstr_fd.o \
        ft_putnbr.o \
        ft_putnbr_fd.o \
        ft_putendl.o \
        ft_putendl_fd.o \
        ft_putchar_fd.o \
        ft_putchar.o \
        ft_memdel.o \
        ft_memalloc.o \
        ft_itoa.o \
        ft_lstdelone.o \
        ft_lstnew.o \
        ft_lstdel.o \
        ft_lstadd.o \
        ft_lstiter.o \
        ft_lstmap.o \
            ft_isspace.o \
            ft_strrev.o \
            ft_lstget_node.o \
            ft_lstpush_back.o \
            ft_to_lower_case.o
SRC_NAME = convert.o \
		do.o \
		ft_itoa_ubase.o \
		ft_printf.o \
		ft_wcslen.o \
		is.o \
		print_c.o \
		print_d.o \
		print_f.o \
		print_o.o \
		print_p.o \
		print_s.o \
		print_str.o \
		print_u.o \
		print_x.o \
		print_per.o \
		not_valid_type.o \
		ft_alloc.o \
		convert_count.o \
		zero.o \
		print_d_2.o \
		fta.o
SRC_LIB = $(addprefix $(LIB_PATH), $(LIB))
OBJ = $(SRC_LIB) $(SRC_NAME)
FLAGS = -Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

$(LIB): %.o: $(LIB_PATH)%.c
		@$(CC) -c $(FLAGS) -I $(LIB_PATH) $< -o $@

$(SRC_NAME): %.o: %.c
		@$(CC) -c $(FLAGS) -I $(LIB_PATH) $< -o $@

clean:
		rm -f $(OBJ) ft_printf.h.gch $(LIB_PATH)libft.a

fclean: clean
		rm -f $(NAME)

re: fclean all