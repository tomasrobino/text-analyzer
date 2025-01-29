cmake_minimum_required(VERSION 3.30)
project(text_analyzer C)

set(CMAKE_C_STANDARD 99)

add_executable(text_analyzer main.c)
configure_file(test.txt test.txt COPYONLY)