cmake_minimum_required(VERSION 3.28)
project(Math)

set(CMAKE_CXX_STANDARD 17)

add_library(Math STATIC
        include/Matrix.hpp
        src/Matrix.cpp
        include/Point3D.hpp
        src/Point3D.cpp
        include/Ray3D.hpp
        src/Ray3D.cpp
        include/Rectangle3D.hpp
        src/Rectangle3D.cpp
        include/Vector3D.hpp
        src/Vector3D.cpp)
