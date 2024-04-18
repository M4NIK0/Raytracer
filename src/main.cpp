#include <iostream>
#include "Render/Camera.hpp"
#include "Primitives/Objects/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/Renderer.hpp"
#include "Light/ILight.hpp"
#include "Light/Objects/PointLight.hpp"

#define SIZE 512
#define WIDTH SIZE
#define HEIGHT SIZE

#include <chrono>

int main()
{
    int width = WIDTH;
    int height = HEIGHT;
    raytracer::Rectangle3D screen(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 0, 0),
                                  raytracer::Vector3D(0, 1, 0));
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, width, height);

    raytracer::Renderer renderer(camera);

    std::vector<std::unique_ptr<raytracer::IPrimitive>> objects;

    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(-5, 5, -35), 5, raytracer::Color(255, 0, 255)));
    renderer.addObject(std::make_shared<raytracer::Sphere>(raytracer::Point3D(5, 7, -20), 3, raytracer::Color(0, 255, 255)));
    renderer.addObject(
            std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, 5010.5, 0), 5000, raytracer::Color(255, 255, 255)));

//    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(150, 0, -35), 10000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(0, -200, -35), 400000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 0, 0), raytracer::Point3D(50, -200, -35), 400000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(-50, -200, -35), 400000));
//    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(-200, 0, -35), 100));

    sfml display;

    display.initImage(width, height);
    // Initialize the window
    display.initWindow(1200, 1200);

    std::vector<std::vector<std::vector<raytracer::RenderRay>>> color_matrix;
    int images_amount = 0;


    int frame = 0;
    bool loop = true;
    while (loop)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        double max_intensity = 0;
        display.clearWindow();

        images_amount++;
        color_matrix.push_back(std::vector<std::vector<raytracer::RenderRay>>());

//        renderer.objects[0]->move(raytracer::Vector3D(0.1, 0, 0));

        for (int x = 0; x < width; x++)
        {
            color_matrix[images_amount - 1].push_back(std::vector<raytracer::RenderRay>());
            for (int y = 0; y < height; y++)
            {
                raytracer::RenderRay ray = renderer.traceRay(x, y);
                color_matrix[images_amount - 1][x].push_back(ray);
                if (ray.intensity > max_intensity)
                    max_intensity = ray.intensity;
            }
        }

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                raytracer::RenderRay color = color_matrix[images_amount - 1][x][y];
                raytracer::Color mean_color(0, 0, 0);

                for (int i = 0; i < images_amount; i++)
                {
                    mean_color = mean_color + raytracer::Renderer::getColorFromLight(color_matrix[i][x][y], max_intensity);
                }

                mean_color = mean_color * (1.0 / images_amount);

                display.drawPixel(x, y, mean_color);
            }
        }

        if (display.getEvent() == 1)
        {
            loop = false;
        }
        if (display.getEvent() == 2)
        {
            width *= 1.5;
            height *= 1.5;
            display.initImage(width, height);
            images_amount = 0;
            color_matrix.clear();
        }
        display.displayScreen();
        frame++;
    }

    // End the window
    display.endWindow();

    return 0;
}
