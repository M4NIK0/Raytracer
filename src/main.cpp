#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include "Objects/Primitives/Plane.hpp"
#include "Objects/Primitives/Cube.hpp"
#include "Objects/Advanced/WavefontObject.hpp"

#include "sfml/sfml.hpp"
#include "Render/RenderProcessWrapper.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 1280
#define HEIGHT 720

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32

#define MAX_SAMPLES 2

#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"
#include "Parser/Parser.hpp"

int main(int ac, char **av)
{
    raytracer::RenderProcessWrapper renderProcessWrapper(WIDTH, HEIGHT, 30);
    renderProcessWrapper.initCamera(250, 1, raytracer::Point3D(0, 1, 0), raytracer::Vector3D(-45, 0, 0));
    renderProcessWrapper.initRenderData(CHUNK_SIZE_X, CHUNK_SIZE_Y, MAX_SAMPLES);

    int width = WIDTH;
    int height = HEIGHT;
    std::string path = "info.txt";

    raytracer::Renderer renderer(raytracer::Camera(width, height));
    renderer.camera.move(raytracer::Vector3D(0, 1, 2));
    renderer.camera.rotate(raytracer::Vector3D(-10, 0, 0));
    renderer.camera.sensitivity = 250;
    renderer.camera.exposure = 0.1;

    renderer.renderData.height = HEIGHT;
    renderer.renderData.width = WIDTH;
    renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    renderer.renderData.maxSamples = MAX_SAMPLES;

    Parser parser;
    parser.parseConfig(path.c_str());
    renderer = parser.parseScene(width, height);

    renderProcessWrapper.renderImageDisplay(1024);

    // Create PPM Output
    raytracer::PPMOutput output("./output.ppm", width, height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            raytracer::Color color = renderProcessWrapper.getPixelColor(x, y);
            output.setPixel(x, y, color);
        }
    }
    output.writeToFile();

    return 0;
}
