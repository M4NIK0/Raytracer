cmake_minimum_required(VERSION 3.28)
project(dummyLight)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3 -fPIC -shared")

add_executable(dummyLight
        src/EntryPoint.cpp)
