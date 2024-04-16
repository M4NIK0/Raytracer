#include <iostream>
#include "Render/Camera.hpp"
#include "Primitives/Objects/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"

int main() {

    raytracer::Rectangle3D screen(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 0, 0), raytracer::Vector3D(0, 1, 0));
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, 600, 600);

    std::vector<std::unique_ptr<raytracer::IPrimitive>> objects;

    objects.push_back(std::make_unique<raytracer::Sphere>(raytracer::Point3D(0.5, 3, -10), 1, raytracer::Color(255, 0, 0)));
    objects.push_back(std::make_unique<raytracer::Sphere>(raytracer::Point3D(253, 1, -10), 250, raytracer::Color(0, 255, 0)));
    objects.push_back(std::make_unique<raytracer::Sphere>(raytracer::Point3D(0.6, -1, -10), 1, raytracer::Color(0, 0, 255)));
    objects.push_back(std::make_unique<raytracer::Sphere>(raytracer::Point3D(-4, -3, -10), 1, raytracer::Color(255, 255, 0)));

    sfml display;

    // Initialize the window
    display.initWindow();

    bool loop = true;
    while (loop)
    {
        display.clearWindow();
        // Generate noise for each pixel
        for (int x = 0; x < 600; ++x) {
            for (int y = 0; y < 600; ++y) {
                raytracer::Ray3D ray = camera.getRay(x, y);
                for (auto &object : objects) {
                    if (object->hits(ray)) {
                        display.drawPixel(x, y, object->getColor());
                        for (auto &object2 : objects) {
                            if (object2 == object)
                            {
                                continue;
                            }
                            if (object2->hits(object->hitReflectedRay(ray))) {
                                display.drawPixel(x, y, object2->getColor());
                            }
                        }
                    }
                }
            }
        }
        objects[3]->move(raytracer::Vector3D(0, 0.1, 0));
        if (display.getEvent() == 1)
        {
            loop = false;
        }
        display.displayScreen();
    }

    // End the window
    display.endWindow();

    return 0;
}
