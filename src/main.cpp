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

#define MAX_BOUNCES 2

#define MAX_DIFFUSE 2

#define MAX_REFLEXIONS 2

#define BASE_COMMAND_LINE false


#include <chrono>
#include "Render/Threads.hpp"
#include "Output/PPMOutput.hpp"
#include "Parser/Parser.hpp"
#include "Parser/ParseArg.hpp"

int main(int ac, char **av)
{

    ParseArg parseArg(ac, av);

    std::string configFile = parseArg.getConfigFile();
    std::string outputFile = parseArg.getOutputFile();
    int width = parseArg.getImageSize().first;
    int height = parseArg.getImageSize().second;
    int chunkSizeX = parseArg.getChunkSize().first;
    int chunkSizeY = parseArg.getChunkSize().second;
    int windowSize = parseArg.getWindowSize();
    int threads = parseArg.getThreads();
    int maxSamples = parseArg.getSamples();
    int bounces = parseArg.getBounces();
    int diffusionRays = parseArg.getDiffusionRays();
    int reflectionRays = parseArg.getReflectionRays();
    bool cli = parseArg.isCli();
    bool ne = parseArg.isNe();

    raytracer::RenderProcessWrapper renderProcessWrapper(width, height, threads);
    renderProcessWrapper.renderer.renderData.maxBounces = bounces;
    renderProcessWrapper.renderer.renderData.diffuseRays = diffusionRays;
    renderProcessWrapper.renderer.renderData.reflexionsRays = reflectionRays;

    Parser parser;
    parser.parseConfig(configFile.c_str());
    parser.parseScene(width, height, renderProcessWrapper);

    renderProcessWrapper.initRenderData(chunkSizeX, chunkSizeY, maxSamples);

    raytracer::Editor editor(renderProcessWrapper.renderer, 1024);
    editor.run();

    renderProcessWrapper.renderImageDisplay(1024);

    // Create PPM Output
    raytracer::PPMOutput output(outputFile, width, height);
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
