cmake_minimum_required(VERSION 3.28)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracer src/main.cpp
        src/Math/Vector3D.cpp
        src/Math/Point3D.cpp
        src/Math/Point3D.hpp
        src/Math/Ray3D.cpp
        src/Math/Ray3D.hpp
        src/Primitives/IPrimitive.cpp
        src/Primitives/IPrimitive.hpp
        src/Primitives/Objects/Sphere.cpp
        src/Primitives/Objects/Sphere.hpp
)
