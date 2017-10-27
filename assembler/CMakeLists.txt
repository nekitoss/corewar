cmake_minimum_required(VERSION 3.7)
project(untitled1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c libft.h asm.h)
add_executable(untitled1 ${SOURCE_FILES})
target_link_libraries(untitled1 ${CMAKE_SOURCE_DIR}/libft.a)