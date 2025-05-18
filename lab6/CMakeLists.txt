cmake_minimum_required(VERSION 3.10)
project(lab6)

add_library(lab6 ${TYPE} lab6_other.c lab6_header.h)

add_executable(l6 lab6_main.c)

target_link_libraries(l6 lab6)
