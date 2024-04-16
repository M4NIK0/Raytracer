#include <iostream>
#include "Render/Camera.hpp"
#include "Primitives/Objects/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/Renderer.hpp"

int main()
{
    raytracer::Rectangle3D screen(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 0, 0), raytracer::Vector3D(0, 1, 0));
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, 600, 600);

    raytracer::Renderer renderer(camera);

    std::vector<std::unique_ptr<raytracer::IPrimitive>> objects;

    renderer.addObject(std::make_unique<raytracer::Sphere>(raytracer::Point3D(4, 3, -10), 1, raytracer::Color(255, 0, 0)));
    renderer.addObject(std::make_unique<raytracer::Sphere>(raytracer::Point3D(1.5, 3, -10), 1, raytracer::Color(255, 255, 0)));
    renderer.addObject(std::make_unique<raytracer::Sphere>(raytracer::Point3D(1, 7, -10), 4, raytracer::Color(0, 255, 255)));
    renderer.addObject(std::make_unique<raytracer::Sphere>(raytracer::Point3D(1, -1000, -10), 1000, raytracer::Color(255, 255, 255)));

    sfml display;

    // Initialize the window
    display.initWindow();

    bool loop = true;
    while (loop)
    {
        display.clearWindow();

        renderer.objects[0]->move(raytracer::Vector3D(0.05, 0, 0));

        for (int x = 0; x < 600; x++)
        {
            for (int y = 0; y < 600; y++)
            {
                raytracer::Color color = renderer.traceRay(x, y);
                display.drawPixel(x, y, color);
            }
        }

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
