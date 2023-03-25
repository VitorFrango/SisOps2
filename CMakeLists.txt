cmake_minimum_required(VERSION 3.24)
project(SisOps C)

set(CMAKE_C_STANDARD 11)

add_executable(SisOps main.c exec01.c cmd01.c)
add_executable(SisOps main.c cmd01.c cmd01)
add_executable(SisOps main.c exec01)