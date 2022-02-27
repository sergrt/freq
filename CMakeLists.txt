cmake_minimum_required(VERSION 3.10)

project(freq VERSION 0.0.1 DESCRIPTION "Simple freq calculator")

add_subdirectory(src)

configure_file(in.txt "${CMAKE_CURRENT_BINARY_DIR}/src/" COPYONLY)