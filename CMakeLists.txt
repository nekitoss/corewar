cmake_minimum_required(VERSION 3.7)
project(corewar)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/)
FILE(GLOB libft_sources libft/*.c libft/*.h libft/get_next_line/*.c libft/ft_printf/*.c)
ADD_LIBRARY(libft.a STATIC ${libft_sources})
set(SOURCE_FILES main.c corewar.h op.h op.c init_struct.c vm_valid/vm_parse_data.c vm_valid/vm_valid_cmd_file.c
		vm_valid/valid_file_cmd_name.c vm_valid/vm_valid_file_data.c vm_valid/vm_save_data_bot.c
		vm_valid/vm_file_data_check.c nekit_main.c viz/bots_draw.c
		viz/fill_memory.c viz/pause.c viz/set_values.c viz/set_values_2.c viz/start_draw.c viz/drawing.c viz/viz.h vm/functions.c viz/help.c)
add_executable(corewar ${SOURCE_FILES})
target_link_libraries(corewar libft.a ${CURSES_LIBRARIES})