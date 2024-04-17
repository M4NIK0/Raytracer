#include <iostream>
#include "Render/Camera.hpp"
#include "Primitives/Objects/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/Renderer.hpp"
#include "Light/ILight.hpp"
#include "Light/Objects/PointLight.hpp"

#define SIZE 2
#define WIDTH SIZE
#define HEIGHT SIZE

int main()
{
    int width = WIDTH;
    int height = HEIGHT;
    raytracer::Rectangle3D screen(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 0, 0), raytracer::Vector3D(0, 1, 0));
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, width, height);

    raytracer::Renderer renderer(camera);

    std::vector<std::unique_ptr<raytracer::IPrimitive>> objects;

    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, 0, -25), 5, raytracer::Color(255, 255, 255)));
    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, 1010, 0), 1000, raytracer::Color(255, 255, 255)));

    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(35, 0, -35), 500));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 0, 0), raytracer::Point3D(0, 0, -35), 500));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(-35, 0, -35), 500));

    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 255, 255), raytracer::Point3D(0, -50, -25), 1000));

    sfml display;

    display.initImage(width, height);
    // Initialize the window
    display.initWindow(1200, 1200);

    int frame = 0;
    bool loop = true;
    while (loop)
    {
        display.clearWindow();

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
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

        if (frame % 1 == 0)
        {
            width *= 1.5;
            height *= 1.5;
            display.initImage(width, height);
            camera = raytracer::Camera(raytracer::Point3D(0.5, 0.5, 1), screen, width, height);
            renderer.camera = camera;
        }
        frame++;
    }

    // End the window
    display.endWindow();

    return 0;
}
