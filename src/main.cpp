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

    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(-1, 3, -10), 1, raytracer::Color(255, 0, 0)));
//    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(2, 3, -10), 1, raytracer::Color(255, 255, 0)));
    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(1, 10005, -10), 10000, raytracer::Color(255, 255, 255)));

    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 255, 255), raytracer::Point3D(4, -20, -10), 600));
//    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 127, 127), raytracer::Point3D(25, -10, -10), 700));

    sfml display;

    // Initialize the window
    display.initWindow();

    bool loop = true;
    while (loop)
    {
        display.clearWindow();

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
