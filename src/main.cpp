#include <iostream>
#include "Vectors/Vector3D.hpp"

int main()
{
    raytracer::Vector3D vec1(1, 2, 3);
    raytracer::Vector3D vec2(4, 5, 6);

    raytracer::Vector3D vec3 = vec1 + vec2;

    std::cout << "vec3.x: " << vec3.x << std::endl;
    std::cout << "vec3.y: " << vec3.y << std::endl;
    std::cout << "vec3.z: " << vec3.z << std::endl;
    return 0;
}
