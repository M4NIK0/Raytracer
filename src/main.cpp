#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/RenderProcessWrapper.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 160
#define HEIGHT 128

#define WIN_SIZE 800

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16

#define MAX_SAMPLES 5

#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"

int main()
{
    std::cout << "A" << std::endl;
    raytracer::RenderProcessWrapper renderer(WIDTH, HEIGHT, 8);
    std::cout << "B" << std::endl;
    renderer.renderer.camera.move(raytracer::Vector3D(0, 0, 2));
    std::cout << "C" << std::endl;
    renderer.renderer.camera.sensitivity = 150;
    std::cout << "D" << std::endl;
    renderer.renderer.camera.exposure = 0.1;
    std::cout << "E" << std::endl;

    renderer.renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    std::cout << "F" << std::endl;
    renderer.renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    std::cout << "G" << std::endl;
    renderer.renderer.renderData.maxSamples = MAX_SAMPLES;
    std::cout << "G" << std::endl;

    auto obj1 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, -101, -4), 100, raytracer::Color(1, 1, 1));
    std::cout << "I" << std::endl;
    auto obj2 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, 0, -4), 1, raytracer::Color(1, 0, 1));
    std::cout << "J" << std::endl;
    auto obj3 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, 1.7, -4), 0.1, raytracer::Color(1, 1, 1));
    std::cout << "K" << std::endl;
    auto obj4 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.2, 0.5, -9), 1, raytracer::Color(1, 1, 1));
    std::cout << "L" << std::endl;
    auto obj5 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.8, 0, -109), 100, raytracer::Color(0, 1, 1));
    std::cout << "M" << std::endl;
    auto obj6 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(3, 0, -4), 1, raytracer::Color(0, 0, 0));
    std::cout << "N" << std::endl;


    raytracer::Vector3D motion = raytracer::Vector3D(2, 0, 0);
    std::cout << "O" << std::endl;
    raytracer::Vector3D rotation = raytracer::Vector3D(0, 0, 0);
    std::cout << "P" << std::endl;

    obj2->setMotion(motion, rotation);
    obj6->setReflexionIndex(1);

    obj1->setReflexionIndex(0.5);

//    obj2->setGlassState(true);

    renderer.renderer.addObject(obj1);
    renderer.renderer.addObject(obj2);
    renderer.renderer.addObject(obj3);
    renderer.renderer.addObject(obj4);
    renderer.renderer.addObject(obj5);
    renderer.renderer.addObject(obj6);

    renderer.renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 0, 0), raytracer::Point3D(-50, 200, -25), 1000000));
    renderer.renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(0, 200, -25), 1000000));
    renderer.renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(50, 200, -25), 1000000));

    renderer.renderImageCLI();

    // Create PPM Output
    raytracer::PPMOutput output("./output.ppm", WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            raytracer::Color color = renderer.renderer.renderData.renderBuffer[x][y];
            output.setPixel(x, y, color);
        }
    }
    output.writeToFile();

    return 0;
}
