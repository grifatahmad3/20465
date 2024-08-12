cmake_minimum_required(VERSION 3.23)
project(myassm C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -ansi")
add_executable(myassm myassm.c essentials.c essentials.h preasm.c preasm.h)