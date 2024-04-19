#include <iostream>
#include "Render/Camera.hpp"
#include "Primitives/Objects/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/Renderer.hpp"
#include "Light/ILight.hpp"
#include "Light/Objects/PointLight.hpp"

#define SIZE 12
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

    camera.move(raytracer::Vector3D(-5, 5, -20));
    raytracer::Renderer renderer(camera);

    std::vector<std::unique_ptr<raytracer::IPrimitive>> objects;

    auto obj1 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(-5, 5, -35), 5, raytracer::Color(0, 0, 0));
    auto obj2 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(3, 5, -35), 3, raytracer::Color(0, 0, 0));
    auto obj3 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, 5010.5, 0), 5000, raytracer::Color(255, 255, 255));
    auto obj4 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, 5, -550), 500, raytracer::Color(255, 128, 128));
    auto obj5 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(-5, 5, -45), 0.5, raytracer::Color(255, 256, 256));

    obj1->setGlassState(true);
    obj2->setGlassState(true);

    renderer.addObject(obj1);
    renderer.addObject(obj2);
    renderer.addObject(obj3);
    renderer.addObject(obj4);
    renderer.addObject(obj5);

    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(0, -200, 0), 200000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 0, 0), raytracer::Point3D(50, -200, 0), 200000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(-50, -200, 0), 200000));

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

        int event = display.getEvent();
        if (event == 1)
        {
            loop = false;
        }
        display.displayScreen();
        frame++;

        if (event == 2)
        {
            camera.move(raytracer::Vector3D(0, 0, 0.5));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (event == 3)
        {
            camera.move(raytracer::Vector3D(0, 0, -0.5));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (event == 4)
        {
            camera.move(raytracer::Vector3D(-0.5, 0, 0));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (event == 5)
        {
            camera.move(raytracer::Vector3D(0.5, 0, 0));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (event == 6)
        {
            camera.move(raytracer::Vector3D(0, 0.5, 0));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (event == 7)
        {
            camera.move(raytracer::Vector3D(0, -0.5, 0));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (event == 8)
        {
            camera.rotate(raytracer::Vector3D(0, 0, 1));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (event == 9)
        {
            camera.rotate(raytracer::Vector3D(0, 0, -1));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (event == 10)
        {
            camera.rotate(raytracer::Vector3D(0, 1, 0));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (event == 11)
        {
            camera.rotate(raytracer::Vector3D(0, -1, 0));
            color_matrix.clear();
            images_amount = 0;
            renderer.camera = camera;
            width = 16;
            height = 16;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }

        if (frame % (width / 2) == 0 && width < 81 && height < 81)
        {
            width *= 1.5;
            height *= 1.5;
            display.initImage(width, height);
            images_amount = 0;
            camera.width = width;
            camera.height = height;
            renderer.camera = camera;
            color_matrix.clear();
        }
    }

    // End the window
    display.endWindow();

    return 0;
}
