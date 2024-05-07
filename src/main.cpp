#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/Renderer.hpp"
#include "Light/ILight.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIN_SIZE 1024

#define WIDTH 640
#define HEIGHT 480

#define CHUNK_SIZE_X 20
#define CHUNK_SIZE_Y 20

#define MAX_SAMPLES 1

#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"

int main()
{
    raytracer::Camera camera(WIDTH, HEIGHT);
    raytracer::Renderer renderer(camera);
    renderer.camera.move(raytracer::Vector3D(0, 0, 2));

    renderer.renderData.width = WIDTH;
    renderer.renderData.height = HEIGHT;
    renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    renderer.renderData.maxSamples = MAX_SAMPLES;
    renderer.renderData.initRenderBuffer();

    auto obj1 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, -101, -4), 100, raytracer::Color(1, 1, 1));
    auto obj2 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, 0, -4), 1, raytracer::Color(1, 0, 1));
    auto obj3 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, 1.7, -4), 0.1, raytracer::Color(1, 1, 1));
    auto obj4 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.2, 0.5, -9), 1, raytracer::Color(1, 1, 1));
    auto obj5 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.8, 0, -109), 100, raytracer::Color(0, 1, 1));
    auto obj6 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(2.5, 0, -4), 2, raytracer::Color(1, 1, 0));

    raytracer::Vector3D motion = raytracer::Vector3D(2, 2, 2);
    raytracer::Vector3D rotation = raytracer::Vector3D(0, 0, 0);

    obj2->setMotion(motion, rotation);
    obj2->initiateMotion(0.5, MAX_SAMPLES);
    obj6->setReflexionIndex(1);

    obj1->setReflexionIndex(0.5);

//    obj2->setGlassState(true);

    renderer.addObject(obj1);
    renderer.addObject(obj2);
    renderer.addObject(obj3);
    renderer.addObject(obj4);
    renderer.addObject(obj5);
    renderer.addObject(obj6);

    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 0, 0), raytracer::Point3D(-50, 200, -25), 1000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(0, 200, -25), 1000));
    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(50, 200, -25), 1000));

    sfml display;

    display.initImage(WIDTH, HEIGHT);
    // Initialize the window

    int maxSize = std::max(WIDTH, HEIGHT);
    double realWidth = (double)WIDTH / (double)maxSize;
    double realHeight = (double)HEIGHT / (double)maxSize;

    display.initWindow((int)(realWidth * WIN_SIZE), (int)(realHeight * WIN_SIZE));

    int images_amount = 0;

    int frame = 0;
    bool loop = true;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    double max_intensity = 0;
    display.clearWindow();

    images_amount++;

    raytracer::Threads threads(renderer);
    std::cout << "Starting render, monitoring render time..." << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  
    for (int i = 0; i < MAX_SAMPLES; i++)
    {
        std::cout << "Sample " << i + 1 << "/" << MAX_SAMPLES << std::endl;
        threads.startThreads(30, CHUNK_SIZE_X, CHUNK_SIZE_Y);
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

        renderer.stepMotions();
    }
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
    }

    // End the window
    display.endWindow();

    // Create PPM Output
    raytracer::PPMOutput output("./output.ppm", WIDTH, HEIGHT);
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            raytracer::Color color = renderer.renderData.renderBuffer[x][y];
            output.setPixel(x, y, color);
        }
    }
    output.writeToFile();

    return 0;
}
