UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	CC = gcc
endif
ifeq ($(UNAME), Linux)
	CC = c99
endif

FAST = -Ofast

FLAGS = -Wall -Wextra -Werror

NAME = corewar

SRC = nekit_main.c

OBJ = $(SRC:.c=.o)

LIBOBJ = libft/*.o

INC = -I ./ -I ./libft/

LIB = -L ./libft -lft

LIBMAKE = make -C libft/

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIBMAKE) all
	@$(CC) $(FLAGS) $(INC) $(LIB) $(OBJ) -o $(NAME)
	@echo  "\033[32mCompiled and created lem-in binary\033[0m"

%.o: %.c
	@$(CC) $(INC) $(FAST) $(FLAGS) -c -o $@ $<

clean: libclean
	@rm -f $(OBJ)
	@echo "\033[01;31mLem-in object files deleted\033[0m"

fclean: libfclean clean
	@rm -rf *.dSYM
	@rm -f $(NAME) a.out
	@echo "\033[01;31mLem-in binary file deleted\033[0m"

re: fclean all

liball:
	@$(LIBMAKE) all

libclean:
	@$(LIBMAKE) clean
libfclean:
	@$(LIBMAKE) fclean

libre:
	@$(LIBMAKE) re
