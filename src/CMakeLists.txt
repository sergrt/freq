cmake_minimum_required(VERSION 3.10)

project(freq)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE
    freq.cpp
    Trie.cpp
    TrieSaver.cpp)

set(HEADER
    Trie.h
    TrieSaver.h)

add_executable(freq ${SOURCE} ${HEADER})
