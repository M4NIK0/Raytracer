cmake_minimum_required(VERSION 3.28)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -O0 -fsanitize=address,leak,undefined -fno-omit-frame-pointer")

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(libconfig++ REQUIRED)

add_executable(raytracer src/main.cpp
        src/Math/Vector3D.cpp
        src/Math/Point3D.cpp
        src/Math/Point3D.hpp
        src/Math/Ray3D.cpp
        src/Math/Ray3D.hpp
        src/Objects/IObject.hpp
        src/Objects/Primitives/Sphere.cpp
        src/Objects/Primitives/Sphere.hpp
        src/Render/Camera.cpp
        src/Render/Camera.hpp
        src/Math/Rectangle3D.cpp
        src/Math/Rectangle3D.hpp
        src/sfml/sfml.cpp
        src/sfml/sfml.hpp
        src/Render/Renderer.cpp
        src/Render/Renderer.hpp
        src/Light/ILight.hpp
        src/Light/Objects/PointLight.cpp
        src/Light/Objects/PointLight.hpp
        src/Render/RenderRay.cpp
        src/Render/RenderRay.hpp
        src/Math/Matrix.cpp
        src/Math/Matrix.hpp
        src/Render/RenderPoint.cpp
        src/Render/RenderPoint.hpp
        src/Render/Chunk.hpp
        src/Render/RenderData.cpp
        src/Render/RenderData.hpp
        src/Render/Threads.cpp
        src/Render/Threads.hpp
        src/Output/PPMOutput.cpp
        src/Parser/Parser.cpp
        src/Parser/Parser.hpp
)

# Link SFML
target_link_libraries(raytracer sfml-graphics sfml-window sfml-system config++)
