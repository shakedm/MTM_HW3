cmake_minimum_required(VERSION 3.7)
project(hw3wet)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors -DNDEBUG")
link_directories(libmtm/win64)
set(SOURCE_FILES main.c list.h mtm_ex3.h set.h company.h room.h EscapeTechnion.h company.c escaper.h escaper.c)
add_executable(hw3wet ${SOURCE_FILES})
target_link_libraries(hw3wet ${CMAKE_SOURCE_DIR}/libmtm.a)