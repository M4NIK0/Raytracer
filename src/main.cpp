#include <iostream>
#include "Render/Camera.hpp"
#include "Render/Editor/Editor.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/RenderProcessWrapper.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 512
#define HEIGHT 512

#define CHUNK_SIZE_X 64
#define CHUNK_SIZE_Y 64

#define MAX_SAMPLES 5

#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"

int main()
{
    raytracer::RenderProcessWrapper renderer(WIDTH, HEIGHT, 8);
    renderer.renderer.camera.move(raytracer::Vector3D(0, 0, 2));
    renderer.renderer.camera.sensitivity = 250;
    renderer.renderer.camera.exposure = 0.01;

    renderer.renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    renderer.renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    renderer.renderer.renderData.maxSamples = MAX_SAMPLES;

    auto obj1 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, -101, -4), 100, raytracer::Color(1, 1, 1));
    auto obj2 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, 1, -4), 1, raytracer::Color(1, 0, 1));
    auto obj3 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, 1.7, -4), 0.1, raytracer::Color(1, 1, 1));
    auto obj4 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.2, 0.5, -9), 1, raytracer::Color(1, 1, 1));
    auto obj5 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.8, 0, -109), 100, raytracer::Color(0, 1, 1));
    auto obj6 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(3, 0, -4), 1, raytracer::Color(0, 0, 0));


    raytracer::Vector3D motion = raytracer::Vector3D(10, 10, 0);
    raytracer::Vector3D rotation = raytracer::Vector3D(0, 0, 0);

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

    renderer.renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 0, 0), raytracer::Point3D(-50, 200, -25), 40000));
    renderer.renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(0, 200, -25), 40000));
    renderer.renderer.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(50, 200, -25), 40000));

    raytracer::editor editor(renderer.renderer, &renderer.display);
    editor.run(800);
    //renderer.renderImageDisplay(800);

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
