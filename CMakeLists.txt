cmake_minimum_required(VERSION 3.7)
project(hw3wet)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors -DNDEBUG")
link_directories(libmtm/win64)
set(SOURCE_FILES usefullFunctions.c usefullFunctions.h main.c mtm_ex3.h room.h room.c  order.h order.c company.h company.c escaper.c escaper.h
        EscapeTechnion.c EscapeTechnion.h list.h set.h types_and_defines.h faculty.h faculty.c)
add_executable(hw3wet ${SOURCE_FILES})
target_link_libraries(hw3wet ${CMAKE_SOURCE_DIR}/libmtm.a)