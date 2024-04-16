#include <iostream>
#include "Render/Camera.hpp"
#include "Primitives/Objects/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"

raytracer::Color generateNoise()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    return raytracer::Color(dis(gen), dis(gen), dis(gen));
}

int main() {

    raytracer::Rectangle3D screen(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 0, 0), raytracer::Vector3D(0, 1, 0));
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, 600, 600);

    raytracer::Sphere sphere(raytracer::Point3D(0.5, 0.5, -4), 1);
    raytracer::Sphere sphere2(raytracer::Point3D(2, 2, -6), 1);

    sfml display;

    // Initialize the window
    display.initWindow();

    // Generate noise for each pixel
    for (int x = 0; x < 600; ++x) {
        for (int y = 0; y < 600; ++y) {
            raytracer::Color color = generateNoise();
            if (sphere.hits(camera.getRay(x, y))) {
                color = raytracer::Color(255, 255, 255);
            } else if (sphere2.hits(camera.getRay(x, y))) {
                color = raytracer::Color(255, 0, 0);
                if (sphere.hits(sphere2.hitReflectedRay(camera.getRay(x, y)))) {
                    color = raytracer::Color(0, 255, 0);
                }
            } else {
                color = raytracer::Color(0, 0, 0);
            }
            display.drawPixel(x, y, color);
        }
    }
    display.displayScreen();

    bool loop = true;
    while (loop)
    {
        if (display.getEvent() == 1)
            loop = false;
    }

    // End the window
    display.endWindow();

    return 0;
}
