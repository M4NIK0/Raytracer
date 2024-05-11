#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include "Objects/Primitives/Plane.hpp"
#include "Objects/Primitives/Cube.hpp"
#include "Objects/Advanced/WavefontObject.hpp"

#include "sfml/sfml.hpp"
#include "Render/RenderProcessWrapper.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 1024
#define HEIGHT 1024

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16

#define MAX_SAMPLES 1

#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"

int main()
{
    raytracer::RenderProcessWrapper renderProcessWrapper(WIDTH, HEIGHT, 30);
    renderProcessWrapper.initCamera(250, 1);
    renderProcessWrapper.initRenderData(CHUNK_SIZE_X, CHUNK_SIZE_Y, MAX_SAMPLES);

    auto obj1 = std::make_shared<raytracer::Plane>(raytracer::Point3D(0, 0, 0), raytracer::Vector3D(0, 1, 0), raytracer::Color(1, 1, 1));
    auto obj2 = std::make_shared<raytracer::WavefontObject>("./untitled.obj", raytracer::Point3D(0.5, 0.5, -2), raytracer::Color(1, 0.6, 0));

    obj2->rotate(raytracer::Vector3D(0, 45, 0));
    obj2->rotate(raytracer::Vector3D(45, 0, 0));

    renderProcessWrapper.addObject(obj1);
    renderProcessWrapper.addObject(obj2);

    renderProcessWrapper.addLight(std::make_shared<raytracer::PointLight>(raytracer::Color(255, 255, 255), raytracer::Point3D(-5, 200, 50), 60000));

    renderProcessWrapper.renderImageDisplay(1024);

    // Create PPM Output
    raytracer::PPMOutput output("./output.ppm", WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            raytracer::Color color = renderProcessWrapper.getPixelColor(x, y);
            output.setPixel(x, y, color);
        }
    }
    output.writeToFile();

    return 0;
}