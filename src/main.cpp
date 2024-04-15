#include <iostream>
#include "Primitives/Objects/Sphere.hpp"

int main()
{
    raytracer::Point3D point(5, 5, 5);
    raytracer::Point3D point2(10, 10, 10);
    point2 = point;

    std::cout << "Point: " << point << std::endl;
    std::cout << "Point2: " << point2 << std::endl;

    raytracer::Sphere sphere(point, 1);
    std::cout << "Sphere: " << sphere.position << " " << sphere.radius << std::endl;
    raytracer::Ray3D ray(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 0, 1));
    std::cout << "Ray: " << ray.origin << " " << ray.direction << std::endl;
    std::cout << "Sphere hits: " << sphere.hits(ray) << std::endl;
    return 0;
}
