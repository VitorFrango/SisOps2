cmake_minimum_required(VERSION 3.24)
project(SisOps C)

set(CMAKE_C_STANDARD 11)

add_executable(SisOps main.c exec01.c cmd01.c)
add_executable(SisOps main.c cmd01.c cmd01)
add_executable(SisOps main.c exec01)
add_executable(SisOps main.c fork01.c fork01)
add_executable(SisOps main.c fork02.c fork02)
add_executable(SisOps main.c fork03.c fork03)