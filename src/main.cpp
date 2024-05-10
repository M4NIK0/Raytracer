#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include "Objects/Primitives/Plane.hpp"
#include "Objects/Primitives/Cube.hpp"
#include "Objects/Advanced/WavefontObject.hpp"

#include "sfml/sfml.hpp"
#include "Render/RenderProcessWrapper.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 720
#define HEIGHT 720

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16

#define MAX_SAMPLES 2

#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"
#include "Parser/Parser.hpp"

int main(int ac, char **av)
{
    int width = WIDTH;
    int height = HEIGHT;
    std::string path = "info.txt";

    raytracer::Renderer renderer(raytracer::Camera(width, height));
    renderer.camera.move(raytracer::Vector3D(0, 1, 2));
    renderer.camera.rotate(raytracer::Vector3D(-10, 0, 0));
    renderer.camera.sensitivity = 250;
    renderer.camera.exposure = 0.1;

    renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    renderer.renderData.maxSamples = MAX_SAMPLES;

    Parser parser;
    parser.parseConfig(path.c_str());
    renderer = parser.parseScene(width, height);

    raytracer::Sphere sphere();

    raytracer::RenderProcessWrapper renderProcessWrapper(renderer, 4);

    renderProcessWrapper.renderImageDisplay(1024);

    // Create PPM Output
    raytracer::PPMOutput output("./output.ppm", width, height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            raytracer::Color color = renderProcessWrapper.renderer.renderData.renderBuffer[x][y];
            output.setPixel(x, y, color);
        }
    }
    output.writeToFile();

    return 0;
}
