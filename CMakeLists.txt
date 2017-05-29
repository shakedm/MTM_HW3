cmake_minimum_required(VERSION 3.7)
project(hw3wet)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c list.h list_mtm1.h mtm_ex3.h set.h libmtm.c)
add_executable(hw3wet ${SOURCE_FILES})