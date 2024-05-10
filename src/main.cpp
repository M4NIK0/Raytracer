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
    int width = 720;
    int height = 720;
    char path[] = "info.txt";

    raytracer::RenderProcessWrapper renderer(width, height, 30);
    renderer.renderer.camera.move(raytracer::Vector3D(0, 1, 2));
    renderer.renderer.camera.rotate(raytracer::Vector3D(-10, 0, 0));
    renderer.renderer.camera.sensitivity = 250;
    renderer.renderer.camera.exposure = 0.1;

    renderer.renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    renderer.renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    renderer.renderer.renderData.maxSamples = MAX_SAMPLES;

    Parser parser;
    parser.parseConfig(path);
    renderer.renderer = parser.parseScene(width, height);

    renderer.renderImageDisplay(1024);

    // Create PPM Output
    raytracer::PPMOutput output("./output.ppm", width, height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            raytracer::Color color = renderer.renderer.renderData.renderBuffer[x][y];
            output.setPixel(x, y, color);
        }
    }
    output.writeToFile();

    return 0;
}
