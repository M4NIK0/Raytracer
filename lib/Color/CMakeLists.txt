cmake_minimum_required(VERSION 3.28)
project(Color)

set(CMAKE_CXX_STANDARD 17)

add_library(Color STATIC
        src/Color.cpp
        include/Color.hpp
)
