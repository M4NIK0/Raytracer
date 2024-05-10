#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include "Objects/Primitives/Plane.hpp"
#include "Objects/Primitives/Cube.hpp"

#include "sfml/sfml.hpp"
#include "Render/RenderProcessWrapper.hpp"
#include "Light/Objects/PointLight.hpp"
#include "Parser/Parser.hpp"

#define WIDTH 1920
#define HEIGHT 1080

#define CHUNK_SIZE_X 64
#define CHUNK_SIZE_Y 64

#define MAX_SAMPLES 20

#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"

int main()
{
    raytracer::RenderProcessWrapper renderer(WIDTH, HEIGHT, 8);
    renderer.renderer.camera.move(raytracer::Vector3D(0, 1, 2));
    renderer.renderer.camera.rotate(raytracer::Vector3D(-10, 0, 0));
    renderer.renderer.camera.sensitivity = 250;
    renderer.renderer.camera.exposure = 0.1;

    renderer.renderer.renderData.chunkWidth = CHUNK_SIZE_X;
    renderer.renderer.renderData.chunkHeight = CHUNK_SIZE_Y;
    renderer.renderer.renderData.maxSamples = MAX_SAMPLES;

    Parser parser;
    parser.parseConfig("info.txt");
    renderer.renderer = parser.parseScene();

    renderer.renderImageDisplay(80);

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
