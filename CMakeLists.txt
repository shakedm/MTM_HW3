cmake_minimum_required(VERSION 3.7)
project(hw3wet)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors -DNDEBUG")

set(SOURCE_FILES usefullFunctions.c usefullFunctions.h mtm_ex3.h room.h room.c company.h company.c
        main.c EscapeTechnion.h EscapeTechnion.c order.h order.c list.h set.h escaper.h escaper.c )
link_directories(libmtm/win64)
add_executable(hw3wet ${SOURCE_FILES})
target_link_libraries(hw3wet ${CMAKE_SOURCE_DIR}/libmtm.a)