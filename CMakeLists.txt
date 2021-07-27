cmake_minimum_required(VERSION 3.17)
project(3_10 C)

set(CMAKE_C_STANDARD 11)

add_executable(3_10 main.c circular_buffer.c circular_buffer.h)