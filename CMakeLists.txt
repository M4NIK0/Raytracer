cmake_minimum_required(VERSION 3.28)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(raytracer src/main.cpp
        include/display.hpp
        src/sfml/sfml.cpp
        src/sfml/sfml.hpp)

# Link SFML
target_link_libraries(raytracer sfml-graphics sfml-window sfml-system)
