#include <iostream>
#include "Primitives/Objects/Sphere.hpp"

int main()
{
    raytracer::Sphere sphere(1, raytracer::Point3D(5, 5, 5));
    raytracer::Ray3D ray(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 1, 1));
    std::cout << sphere.hits(ray) << std::endl;
    return 0;
}
