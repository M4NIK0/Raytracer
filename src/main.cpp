#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/Renderer.hpp"
#include "Light/ILight.hpp"
#include "Light/Objects/PointLight.hpp"

#define SIZE 1024
#define WIDTH SIZE
#define HEIGHT SIZE

#define CHUNKS 2
#define CHUNKS_X CHUNKS
#define CHUNKS_Y CHUNKS

#define CHUNK_SIZE_X WIDTH / CHUNKS_X
#define CHUNK_SIZE_Y HEIGHT / CHUNKS_Y

#define MAX_SAMPLES 1

#include <chrono>

int main()
{
    int width = WIDTH;
    int height = HEIGHT;

    raytracer::Rectangle3D screen(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(1, 0, 0),
                                  raytracer::Vector3D(0, 1, 0));
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, width, height);
    camera.move(raytracer::Vector3D(5, -5, 0));

//    camera.move(raytracer::Vector3D(-1.5, 5, -15));
    raytracer::Renderer renderer(camera);

    std::vector<std::unique_ptr<raytracer::IObject>> objects;

    auto obj1 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, -5, -25), 5, raytracer::Color(0.1, 0.1, 0.1));
    auto obj2 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(10, -5, -25), 5, raytracer::Color(1, 1, 1));
    auto obj3 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, 10000, -25), 9999, raytracer::Color(1, 1, 1));
    auto obj4 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, -15, -25), 1, raytracer::Color(1, 1, 1));

    obj1->setReflexionIndex(0.1);
    obj2->setReflexionIndex(0.95);
    obj3->setReflexionIndex(0.25);

    renderer.addObject(obj1);
    renderer.addObject(obj2);
    renderer.addObject(obj3);
    renderer.addObject(obj4);

    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(0, -20, 0), 1000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 0, 0), raytracer::Point3D(10, -20, 0), 1000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(-10, -20, 0), 1000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 255, 255), raytracer::Point3D(0, -20, -50), 1000));
//    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 255, 255), raytracer::Point3D(0, -20, 0), 1000));

    sfml display;

    display.initImage(width, height);
    // Initialize the window
    display.initWindow(1200, 1200);

    std::vector<std::vector<std::vector<raytracer::RenderRay>>> color_matrix;
    int images_amount = 0;

    int frame = 0;
    bool loop = true;

    for (int i = 0; i < MAX_SAMPLES; i++)
    {
        color_matrix.push_back(std::vector<std::vector<raytracer::RenderRay>>());
        for (int x = 0; x < width; x++)
        {
            color_matrix[i].push_back(std::vector<raytracer::RenderRay>());

            for (int y = 0; y < height; y++)
            {
                color_matrix[i][x].push_back(raytracer::RenderRay());
            }
        }
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    double max_intensity = 0;
    display.clearWindow();

    images_amount++;

//        renderer.objects[0]->move(raytracer::Vector3D(0.1, 0, 0));

    for (int chunk_x = 0; chunk_x < CHUNKS_X; chunk_x++)
    {
        for (int chunk_y = 0; chunk_y < CHUNKS_Y; chunk_y++)
        {
            for (int i = 0; i < MAX_SAMPLES; i++)
            {
                for (int x = 0; x < CHUNK_SIZE_X; x++)
                {
                    for (int y = 0; y < CHUNK_SIZE_Y; y++)
                    {
                        raytracer::RenderRay ray = renderer.traceRay(x + (chunk_x * CHUNK_SIZE_X), y + (chunk_y * CHUNK_SIZE_Y));
                        color_matrix[i][x + (chunk_x * CHUNK_SIZE_X)][y + (chunk_y * CHUNK_SIZE_Y)] = ray;
                        if (ray.getColor().r > max_intensity)
                            max_intensity = ray.getColor().r;
                        if (ray.getColor().g > max_intensity)
                            max_intensity = ray.getColor().g;
                        if (ray.getColor().b > max_intensity)
                            max_intensity = ray.getColor().b;
                    }
                }
            }

            for (int x = 0; x < WIDTH; x++)
            {
                for (int y = 0; y < HEIGHT; y++)
                {
                    raytracer::Color color(0, 0, 0);
                    for (int i = 0; i < MAX_SAMPLES; i++)
                    {
                        color = color + color_matrix[i][x][y].getColor();
                    }
                    color = color * (1.0 / MAX_SAMPLES);
                    color = color * (255 / max_intensity);
                    color.cap();
                    display.drawPixel(x, y, color);
                }
            }

            display.displayScreen();
        }
    }

    while (loop)
    {

        int event = display.getEvent();
        if (event == 1)
        {
            loop = false;
        }
        display.displayScreen();
        frame++;

//        if (event == 2)
//        {
//            camera.move(raytracer::Vector3D(0, 0, 0.5));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
//
//        if (event == 3)
//        {
//            camera.move(raytracer::Vector3D(0, 0, -0.5));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
//
//        if (event == 4)
//        {
//            camera.move(raytracer::Vector3D(-0.5, 0, 0));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
//
//        if (event == 5)
//        {
//            camera.move(raytracer::Vector3D(0.5, 0, 0));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
//
//        if (event == 6)
//        {
//            camera.move(raytracer::Vector3D(0, 0.5, 0));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
//
//        if (event == 7)
//        {
//            camera.move(raytracer::Vector3D(0, -0.5, 0));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
//
//        if (event == 8)
//        {
//            camera.rotate(raytracer::Vector3D(0, 0, 1));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
//
//        if (event == 9)
//        {
//            camera.rotate(raytracer::Vector3D(0, 0, -1));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
//
//        if (event == 10)
//        {
//            camera.rotate(raytracer::Vector3D(0, 1, 0));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
//
//        if (event == 11)
//        {
//            camera.rotate(raytracer::Vector3D(0, -1, 0));
//            color_matrix.clear();
//            images_amount = 0;
//            renderer.camera = camera;
//            width = 16;
//            height = 16;
//            display.initImage(width, height);
//            images_amount = 0;
//            camera.width = width;
//            camera.height = height;
//            renderer.camera = camera;
//            color_matrix.clear();
//        }
    }

    // End the window
    display.endWindow();

    return 0;
}
