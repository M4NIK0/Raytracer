#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include "Objects/Primitives/Plane.hpp"
#include <random>

#include "sfml/sfml.hpp"
#include "Render/RenderProcessWrapper.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 512
#define HEIGHT 320

#define CHUNK_SIZE_X 1
#define CHUNK_SIZE_Y HEIGHT

#define MAX_SAMPLES 15

#include "Output/PPMOutput.hpp"

int main()
{
    raytracer::RenderProcessWrapper renderer(WIDTH, HEIGHT, 30);
    renderer.renderer.camera.move(raytracer::Vector3D(0, 0, 2));
    renderer.renderer.camera.sensitivity = 250;
    renderer.renderer.camera.exposure = 0.1;

    renderer.renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    renderer.renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    renderer.renderer.renderData.maxSamples = MAX_SAMPLES;

    auto obj1 = std::make_shared<raytracer::Plane>(raytracer::Point3D(20, -1, 0), raytracer::Vector3D(0, 1, 0),
                                                    raytracer::Color(1, 1, 1));
    auto obj2 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, 0.5, -5), 1,
                                                    raytracer::Color(1, 0, 1));
    auto obj3 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0.5, 1.7, -4), 0.1,
                                                    raytracer::Color(1, 1, 1));
    auto obj4 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(0, -0.3, -3), 0.7,
                                                    raytracer::Color(1, 1, 1));
    auto obj5 = std::make_shared<raytracer::Plane>(raytracer::Point3D(-6, 0, -5), raytracer::Vector3D(1, 1, 0), raytracer::Color(1, 1, 1));
    auto obj6 = std::make_shared<raytracer::Sphere>(raytracer::Point3D(3, 0, -4), 1, raytracer::Color(0, 0, 0));

    raytracer::Vector3D motion = raytracer::Vector3D(10, 0, 0);
    raytracer::Vector3D rotation = raytracer::Vector3D(0, 0, 0);

//    obj2->setMotion(motion, rotation);
    obj6->setReflexionIndex(1);

    obj1->setReflexionIndex(0.5);


    obj4->setGlassState(true);

    renderer.renderer.addObject(obj1);
    renderer.renderer.addObject(obj2);
    renderer.renderer.addObject(obj3);
    renderer.renderer.addObject(obj4);
    renderer.renderer.addObject(obj5);
    renderer.renderer.addObject(obj6);

    renderer.renderer.addLight(
            std::make_shared<raytracer::PointLight>(raytracer::Color(255, 0, 0), raytracer::Point3D(-5, 200, -25),
                                                    40000));
    renderer.renderer.addLight(
            std::make_shared<raytracer::PointLight>(raytracer::Color(0, 255, 0), raytracer::Point3D(0, 200, -25),
                                                    40000));
    renderer.renderer.addLight(
            std::make_shared<raytracer::PointLight>(raytracer::Color(0, 0, 255), raytracer::Point3D(5, 200, -25),
                                                    40000));

    renderer.renderImageDisplay();

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
