#include <iostream>
#include "Render/Camera.hpp"
#include "Primitives/Objects/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/Renderer.hpp"
#include "Light/ILight.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 600
#define HEIGHT 600

int main()
{
    raytracer::Rectangle3D screen(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 0, 0), raytracer::Vector3D(0, 1, 0));
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, WIDTH, HEIGHT);

    raytracer::Renderer renderer(camera);

    std::vector<std::unique_ptr<raytracer::IPrimitive>> objects;

    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(4, 3, -10), 1, raytracer::Color(255, 0, 0)));
    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(1.5, 3, -10), 1, raytracer::Color(255, 255, 0)));
//    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(1, 2, -10), 4, raytracer::Color(0, 255, 255)));
    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(1, -1000, -10), 1000, raytracer::Color(255, 255, 255)));

    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 255, 255), raytracer::Point3D(4, 6, -10), 10));

    sfml display;

    // Initialize the window
    display.initWindow();

    bool loop = true;
    while (loop)
    {
        display.clearWindow();

        renderer.objects[0]->move(raytracer::Vector3D(0.05, 0, 0));

        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
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
        std::cout << "loop" << std::endl;
    }

    // End the window
    display.endWindow();

    return 0;
}
