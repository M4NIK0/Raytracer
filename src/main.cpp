#include <iostream>
#include "Render/Camera.hpp"
#include "Objects/Primitives/Sphere.hpp"
#include "Objects/Primitives/Plane.hpp"
#include "Objects/Primitives/Cube.hpp"
#include "Objects/Advanced/WavefontObject.hpp"

#include "Render/Editor/Editor.hpp"
#include "sfml/sfml.hpp"
#include "Render/RenderProcessWrapper.hpp"
#include "Light/Objects/PointLight.hpp"

#define WIDTH 640
#define HEIGHT 360

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16

#define MAX_SAMPLES 1

#define MAX_THREADS 8

#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"
#include "Parser/Parser.hpp"

int main(int ac, char **av)
{
    int width = WIDTH;
    int height = HEIGHT;
    int chunkSizeX = CHUNK_SIZE_X;
    int chunkSizeY = CHUNK_SIZE_Y;
    int maxSamples = MAX_SAMPLES;
    int threads = MAX_THREADS;

    std::string path = "info.txt";

    raytracer::RenderProcessWrapper renderProcessWrapper(width, height, threads);

    Parser parser;
    parser.parseConfig(path.c_str());
    parser.parseScene(width, height, renderProcessWrapper);

    renderProcessWrapper.initRenderData(chunkSizeX, chunkSizeY, maxSamples);

    raytracer::Editor editor(renderProcessWrapper.renderer, 1024);
    editor.run();

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
