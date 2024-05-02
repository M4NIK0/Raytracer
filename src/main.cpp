#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/Renderer.hpp"
#include "Light/ILight.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 64
#define HEIGHT 64

#define CHUNKS_SIZE 26

#define MAX_SAMPLES 3

#include <chrono>

int main()
{
    int width = WIDTH;
    int height = HEIGHT;

    raytracer::Rectangle3D screen(raytracer::Point3D(0, 1, 0), raytracer::Vector3D(1, 0, 0),
                              raytracer::Vector3D(0, -1, 0)); // Invert the Y vector
    raytracer::Camera camera(raytracer::Point3D(0.5, 0.5, 1), screen, width, height);
    raytracer::Renderer renderer(camera);
    raytracer::renderData data;

    data.width = width;
    data.height = height;
    data.chunkWidth = CHUNKS_SIZE;
    data.chunkHeight = CHUNKS_SIZE;
    renderer.data = data;

    auto obj1 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, -101, -4), 100, raytracer::Color(1, 1, 1));
    auto obj2 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, 0.5, -4), 1, raytracer::Color(1, 1, 1));
    auto obj3 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, 1.7, -4), 0.1, raytracer::Color(1, 1, 1));
    auto obj4 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.2, 0.5, -9), 1, raytracer::Color(1, 1, 1));

    obj2->setGlassState(true);

    renderer.addObject(obj1);
    renderer.addObject(obj2);
    renderer.addObject(obj3);
    renderer.addObject(obj4);

    renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 255, 255), raytracer::Point3D(0, 200, -25), 1000));

    sfml display;

    display.initImage(width, height);
    // Initialize the window
    display.initWindow(800, 800);

    std::vector<std::vector<std::vector<raytracer::RenderRay>>> color_matrix;
    std::vector<std::vector<raytracer::RenderRay>> mean_matrix;
    int images_amount = 0;

    int frame = 0;
    bool loop = true;

    for (int i = 0; i < MAX_SAMPLES; i++)
    {
        color_matrix.emplace_back();
        for (int x = 0; x < width; x++)
        {
            color_matrix[i].emplace_back();
            mean_matrix.emplace_back();

            for (int y = 0; y < height; y++)
            {
                color_matrix[i][x].emplace_back();
                mean_matrix[x].emplace_back();
            }
        }
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    double max_intensity = 0;
    display.clearWindow();

    images_amount++;

    std::vector<raytracer::Chunk> chunks = raytracer::Renderer::getChunks(data, CHUNKS_SIZE, CHUNKS_SIZE);

    for (auto &chunk : chunks)
    {
        for (int i = 0; i < MAX_SAMPLES; i++)
        {
            std::vector<std::vector<raytracer::RenderRay>> chunk_matrix = renderer.renderChunk(chunk, data);

            for (int x = 0; x < chunk.width; x++)
            {
                for (int y = 0; y < chunk.height; y++)
                {
                    color_matrix[i][x + (chunk.x * data.chunkWidth)][y + (chunk.y * data.chunkHeight)] = chunk_matrix[x][y];
                }
            }
        }
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            raytracer::Color color = raytracer::Color(0, 0, 0);
            for (int i = 0; i < MAX_SAMPLES; i++)
            {
                color = color + color_matrix[i][x][y].getColor();
            }
            color = color * (1.0 / MAX_SAMPLES);
            mean_matrix[x][y].color = color;
        }
    }

    max_intensity = 0;
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            raytracer::Color color = mean_matrix[x][y].getColor();

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
            raytracer::Color color = mean_matrix[x][y].getColor();
            color = color * (255 / max_intensity);
            color.cap();
            display.drawPixel(x, y, color);
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
