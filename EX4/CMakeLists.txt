cmake_minimum_required(VERSION 3.10)
project(EX4)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -Wfatal-errors -Wno-shift-count-overflow -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-unused-private-field -pedantic-errors")

include_directories(.)

add_executable(EX4
        ex4.h
        main.cpp
        unit_test_util.h GameBoard.h)
