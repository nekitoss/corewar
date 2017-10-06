cmake_minimum_required(VERSION 3.7)
project(corewar)

set(CMAKE_C_STANDARD 99)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/)
FILE(GLOB libft_sources libft/*.c libft/*.h libft/get_next_line/*.c libft/ft_printf/*.c)
ADD_LIBRARY(libft.a STATIC ${libft_sources})
set(SOURCE_FILES main.c corewar.h op.h op.c init_struct.c vm_valid/vm_parse_data.c vm_valid/vm_valid_cmd_file.c vm_valid/valid_file_data.c)
add_executable(corewar ${SOURCE_FILES})
target_link_libraries(corewar libft.a)