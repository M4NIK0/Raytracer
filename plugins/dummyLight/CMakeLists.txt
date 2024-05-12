cmake_minimum_required(VERSION 3.28)
project(dummyLight)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3 -fPIC")

add_subdirectory(../../lib/Math Math)
add_subdirectory(../../lib/Color Color)
find_package(libconfig++ REQUIRED)

add_library(dummyLight SHARED
        src/EntryPoint.cpp
        src/DirectionalLight.cpp
        include/Math/Point3D.hpp
        include/Math/Ray3D.hpp
        include/Math/Vector3D.hpp
)

target_link_libraries(dummyLight Math)
target_link_libraries(dummyLight Color)
target_link_libraries(dummyLight config++)
