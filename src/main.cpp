#include <iostream>
#include "Render/Camera.hpp"
#include "Primitives/Objects/Sphere.hpp"

int main()
{
    raytracer::Rectangle3D screen(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 0, 0), raytracer::Vector3D(0, 1, 0));
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, 50, 50);

    raytracer::Sphere sphere(raytracer::Point3D(0.5, 0.5, -2), 1);

    for (int y = 0; y < 50; y++) {
        for (int x = 0; x < 50; x++) {
            raytracer::Ray3D ray = camera.getRay(x, y);
            std::cout << sphere.hits(ray);
        }
        std::cout << std::endl;
    }
}
