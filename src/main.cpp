#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include "Objects/Primitives/Plane.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/Renderer.hpp"
#include "Light/ILight.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 512
#define HEIGHT 512

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32

#define MAX_SAMPLES 5

#include <chrono>
#include "Render/Threads.hpp"

int main()
{
    raytracer::Rectangle3D screen(raytracer::Point3D(0, 1, 0), raytracer::Vector3D(1, 0, 0),
                              raytracer::Vector3D(0, -1, 0)); // Invert the Y vector
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, WIDTH, HEIGHT);
    raytracer::Renderer renderer(camera);

    renderer.renderData.width = WIDTH;
    renderer.renderData.height = HEIGHT;
    renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    renderer.renderData.maxSamples = MAX_SAMPLES;
    renderer.renderData.initRenderBuffer();

    auto obj1 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, -5, -25), 5, raytracer::Color(1, 1, 1));
    auto obj2 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(10, -5, -25), 5, raytracer::Color(1, 1, 1));

    auto plane = std::make_shared<raytracer::Plane>(raytracer::Point3D(0, 0, -40), raytracer::Vector3D(0, -1, 0), raytracer::Color(1, 1, 1));

//    obj1->setReflexionIndex(0.1);
//    obj2->setReflexionIndex(1);
//    obj3->setReflexionIndex(0.5);

//    obj1->setRefractionIndex(1.5);
//    obj2->setRefractionIndex(1.5);

    plane->rotate(raytracer::Vector3D(-90, 0, 90));

    renderer.addObject(obj1);
    renderer.addObject(obj2);
//    renderer.addObject(obj4);
//    renderer.addObject(obj5);

    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(0, -20, 0), 1000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 0, 0), raytracer::Point3D(10, -20, 0), 1000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(-10, -20, 0), 1000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 255, 255), raytracer::Point3D(0, -20, -50), 1000));

    sfml display;

    display.initImage(WIDTH, HEIGHT);
    // Initialize the window
    display.initWindow(800, 800);

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

    raytracer::Threads threads(renderer);
    std::cout << "Starting render, monitoring render time..." << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    threads.startThreads(16, CHUNK_SIZE_X, CHUNK_SIZE_Y);
    max_intensity = 0;
    while (1)
    {
        if (threads.getRemainingChunks() == 0)
        {
            break;
        }

        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                raytracer::Color color = renderer.renderData.renderBuffer[x][y];

                if (color.r > max_intensity)
                    max_intensity = color.r;
                if (color.g > max_intensity)
                    max_intensity = color.g;
                if (color.b > max_intensity)
                    max_intensity = color.b;
            }
        }

        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                raytracer::Color color = renderer.renderData.renderBuffer[x][y];
                color = color * (255 / max_intensity);
                color.cap();
                display.drawPixel(x, y, color);
            }
        }
        display.displayScreen();
    }

    display.displayScreen();
    threads.stopThreads();
    end = std::chrono::steady_clock::now();

    std::cout << "Rendered in " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "s" << std::endl;


    max_intensity = 0;
        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                raytracer::Color color = renderer.renderData.renderBuffer[x][y];

                if (color.r > max_intensity)
                    max_intensity = color.r;
                if (color.g > max_intensity)
                    max_intensity = color.g;
                if (color.b > max_intensity)
                    max_intensity = color.b;
            }
        }

        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                raytracer::Color color = renderer.renderData.renderBuffer[x][y];
                color = color * (255 / max_intensity);
                color.cap();
                display.drawPixel(x, y, color);
            }
        }
        display.displayScreen();


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
