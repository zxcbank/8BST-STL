cmake_minimum_required(VERSION 3.26)
project(8BST_STL)

set(CMAKE_CXX_STANDARD 20)

add_executable(8BST_STL
        main.cpp
        Tree.h
)

enable_testing()
add_subdirectory(tests)
