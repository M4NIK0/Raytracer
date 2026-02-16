cmake_minimum_required(VERSION 3.5)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -O0 -fno-omit-frame-pointer")

set(CPM_VERSION 0.39.0)

if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
    message(STATUS "Downloading CPM.cmake")
    file(
            DOWNLOAD
            https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_VERSION}/CPM.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    )
endif()

include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage(
        NAME sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG "2.6.2"
        OPTIONS
        "SFML_INSTALL_PKGCONFIG_FILES OFF"
        "SFML_BUILD_AUDIO OFF"
        "SFML_BUILD_NETWORK OFF"
)

CPMAddPackage(
        NAME libconfig
        GIT_REPOSITORY https://github.com/hyperrealm/libconfig.git
        GIT_TAG "v1.8.2"
)

add_subdirectory(lib/Math)
add_subdirectory(lib/Color)

# Find SFML & libconfig++
#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
#find_package(libconfig++ REQUIRED)


add_executable(raytracer src/main.cpp
        include/Math/Point3D.hpp
        include/Math/Ray3D.hpp
        src/Objects/IObject.hpp
        src/Objects/Primitives/Sphere.cpp
        src/Objects/Primitives/Sphere.hpp
        src/Render/Camera.cpp
        src/Render/Camera.hpp
        include/Math/Rectangle3D.hpp
        src/sfml/sfml.cpp
        src/sfml/sfml.hpp
        src/Render/Renderer.cpp
        src/Render/Renderer.hpp
        src/Light/ILight.hpp
        src/Light/Objects/PointLight.cpp
        src/Light/Objects/PointLight.hpp
        src/Render/RenderRay.cpp
        src/Render/RenderRay.hpp
        include/Math/Matrix.hpp
        src/Render/RenderPoint.cpp
        src/Render/RenderPoint.hpp
        src/Objects/Primitives/Plane.hpp
        src/Objects/Primitives/Plane.cpp
        src/Render/Chunk.hpp
        src/Render/RenderData.cpp
        src/Render/RenderData.hpp
        src/Render/Threads.cpp
        src/Render/Threads.hpp
        src/Output/PPMOutput.cpp
        src/Output/PPMOutput.hpp
        src/Render/RenderProcessWrapper.cpp
        src/Render/RenderProcessWrapper.hpp
        src/Objects/Primitives/Triangle.cpp
        src/Objects/Primitives/Triangle.hpp
        src/Objects/Advanced/WavefontObject.cpp
        src/Objects/Advanced/WavefontObject.hpp
        src/Render/Editor/Editor.cpp
        src/Render/Editor/Editor.hpp
        src/Parser/Parser.cpp
        src/Parser/Parser.hpp
        src/Factory/Factory.cpp
        src/Parser/ParseArg.cpp
        src/LibHandler/LibHandler.cpp
)

# Link SFML
target_link_libraries(raytracer Math)
target_link_libraries(raytracer Color)
target_link_libraries(raytracer sfml-graphics sfml-window sfml-system config++)

# Make relocatable: set RPATH so the executable will look for libraries in ../lib at runtime
set(CMAKE_INSTALL_RPATH "\$ORIGIN/../lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Install rules: executable, resources and plugins
install(TARGETS raytracer RUNTIME DESTINATION bin)

# Install built libraries produced by this project so they end up in the package lib/
install(TARGETS Math Color
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION lib
)

# Install public headers so packaged consumers can use them if needed
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/images DESTINATION share/raytracer)
if(EXISTS ${CMAKE_SOURCE_DIR}/plugins)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/plugins DESTINATION lib/raytracer)
endif()

# Use BundleUtilities during install to collect shared library dependencies into the package lib/
# This runs at install time (including when CPack performs an install staging step).
include(BundleUtilities)
install(CODE "include(BundleUtilities)\n"
             "file(MAKE_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/lib\")\n"
             "fixup_bundle(\"${CMAKE_INSTALL_PREFIX}/bin/raytracer\" \"${CMAKE_INSTALL_PREFIX}/share/raytracer\" \"${CMAKE_INSTALL_PREFIX}/lib\")\n"
)

# CPack configuration: produce tar/zip archives containing the installed tree
set(CPACK_PACKAGE_NAME "raytracer")
set(CPACK_PACKAGE_VENDOR "raytracer project")
set(CPACK_PACKAGE_CONTACT "")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_GENERATOR "TGZ;ZIP")
# When packaging, files are placed under this prefix (so binaries default to /usr/bin inside the package)
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")
include(CPack)

