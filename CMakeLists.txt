cmake_minimum_required(VERSION 3.25)
project(Lox C)

set(CMAKE_C_STANDARD 99)

add_executable(Lox main.c common.h chunk.h chunk.c memory.h memory.c debug.h debug.c value.h)
