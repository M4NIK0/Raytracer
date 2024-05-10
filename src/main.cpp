#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include "Objects/Primitives/Plane.hpp"
#include "Objects/Primitives/Cube.hpp"
#include "Objects/Advanced/WavefontObject.hpp"

#include "sfml/sfml.hpp"
#include "Render/RenderProcessWrapper.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 256
#define HEIGHT 256

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16

#define MAX_SAMPLES 2

#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"

int main()
{
    raytracer::RenderProcessWrapper renderer(WIDTH, HEIGHT, 30);
    renderer.renderer.camera.sensitivity = 250;
    renderer.renderer.camera.exposure = 1;

    renderer.renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    renderer.renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    renderer.renderer.renderData.maxSamples = MAX_SAMPLES;

    auto obj1 = std::make_shared<raytracer::Plane>(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(0, 1, 0), raytracer::Color(1, 1, 1));
    auto obj2 = std::make_shared<raytracer::WavefontObject>("./untitled.obj", raytracer::Point3D(0.5, 0.5, -3), raytracer::Color(1, 0, 1));

    obj2->rotate(raytracer::Vector3D(0, 10, 0));

    raytracer::Vector3D motion = raytracer::Vector3D(10, 0, 0);
    raytracer::Vector3D rotation = raytracer::Vector3D(0, 0, 0);

    renderer.renderer.addObject(obj1);
    renderer.renderer.addObject(obj2);
//    renderer.renderer.addObject(obj8);

    renderer.renderer.addLight(
            std::make_shared<raytracer::PointLight>(raytracer::Color(255, 255, 255), raytracer::Point3D(-5, 200, 50), 80000));

    renderer.renderImageDisplay(1024);

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
