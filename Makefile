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

SRC = ./vm/nekit_main.c\
		./vm_valid/main.c\
		./vm_valid/init_struct.c\
		./vm_valid/valid_file_cmd_name.c\
		./vm_valid/vm_file_data_check.c\
		./vm_valid/vm_parse_data.c\
		./vm_valid/vm_save_data_bot.c\
		./vm_valid/vm_valid_cmd_file.c\
		./vm_valid/vm_valid_file_data.c\
		./viz/bots_draw.c\
		./viz/drawing.c\
		./viz/fill_memory.c\
		./viz/pause.c\
		./viz/set_values.c\
		./viz/set_values_2.c\
		./viz/start_draw.c\
		./viz/help.c\
		./vm/hex_print.c\
		./vm_valid/vm_parse_data2.c\
		./vm/func1.c\
		./vm/func2.c\
		./vm/func3.c\
		./vm/func4.c\
		./vm/func5.c\
		./vm/func6.c\
		./vm/func7.c\
		./vm/func8.c\
		./vm/func9.c\
		./vm/func10.c\
		./vm/func11.c

OBJ = $(SRC:.c=.o)

LIBOBJ = libft/*.o

INC = -I ./ -I ./libft/ -I ./viz/

LIB = -L ./libft -lft

LIBMAKE = make -C libft/

MAKEASM = make -C assembler/

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIBMAKE) all
	@$(MAKEASM) all
	@$(CC) $(FLAGS) $(INC) $(LIB) $(OBJ) -lncurses -o $(NAME)
	@echo  "\033[32mCompiled and created Corewar (VM) binary\033[0m"

%.o: %.c
	@$(CC) $(INC) $(FAST) $(FLAGS) -c -o $@ $<

clean: libclean
	@$(MAKEASM) clean
	@rm -f $(OBJ)
	@echo "\033[01;31mCorewar (VM) object files deleted\033[0m"

fclean: libfclean clean
	@$(MAKEASM) fclean
	@rm -rf *.dSYM
	@rm -f $(NAME) a.out
	@echo "\033[01;31mCorewar (VM) binary file deleted\033[0m"

re: fclean all

liball:
	@$(LIBMAKE) all

libclean:
	@$(LIBMAKE) clean
libfclean:
	@$(LIBMAKE) fclean

libre:
	@$(LIBMAKE) re
