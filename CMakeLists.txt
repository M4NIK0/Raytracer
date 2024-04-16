cmake_minimum_required(VERSION 3.28)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(raytracer src/main.cpp
        src/Math/Vector3D.cpp
        src/Math/Point3D.cpp
        src/Math/Point3D.hpp
        src/Math/Ray3D.cpp
        src/Math/Ray3D.hpp
        src/Primitives/IPrimitive.hpp
        src/Primitives/Objects/Sphere.cpp
        src/Primitives/Objects/Sphere.hpp
        src/Render/Camera.cpp
        src/Render/Camera.hpp
        src/Math/Rectangle3D.cpp
        src/Math/Rectangle3D.hpp
        src/sfml/sfml.cpp
        src/sfml/sfml.hpp
        src/Primitives/Objects/Cube.cpp
        src/Primitives/Objects/Cube.hpp
        src/Render/Renderer.cpp
        src/Render/Renderer.hpp
)

# Link SFML
target_link_libraries(raytracer sfml-graphics sfml-window sfml-system)
