cmake_minimum_required(VERSION 3.24)
project(SisOps C)

set(CMAKE_C_STANDARD 11)

add_executable(SisOps main.c fork.c exec01.c cmd01.c fork04.c fork04.c fork04.c)
add_executable(SisOps main.c cmd01.c cmd01 fork04.c fork.c)
add_executable(SisOps main.c exec01 fork04.c)
add_executable(SisOps main.c fork01.c fork01 fork04.c fork04.c fork.c fork_ex4.c)
