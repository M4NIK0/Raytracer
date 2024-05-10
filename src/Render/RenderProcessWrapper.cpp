/*
** EPITECH PROJECT, 2024
** RenderProcessWrapper.cpp
** File description:
** raytracer
*/

#include "RenderProcessWrapper.hpp"

raytracer::RenderProcessWrapper::RenderProcessWrapper(Renderer &rd, size_t nbThreads)
        : renderer(rd), threads(Threads(rd)), _width(rd.renderData.width), _height(rd.renderData.height), _nbThreads(nbThreads)
{
    std::cout << "RenderProcessWrapper created" << std::endl;
    for (auto &object : renderer.renderData.objects)
    {
        std::cout << "Object added" << std::endl;
    }
    for (auto &light : renderer.renderData.lights)
    {
        std::cout << "Light added" << std::endl;
    }
}

raytracer::RenderProcessWrapper::~RenderProcessWrapper() = default;

void raytracer::RenderProcessWrapper::renderImageDisplay(int windowSize)
{
    renderer.renderData.initRenderBuffer();

    if (windowSize > 0)
    {
        int maxSize = std::max(_width, _height);
        double realWidth = (double) _width / (double) maxSize;
        double realHeight = (double) _height / (double) maxSize;

        display.initImage(_width, _height);
        display.initWindow((int) (realWidth * windowSize), (int) (realHeight * windowSize));
    }

    auto begin = std::chrono::steady_clock::now();

    renderer.initMotions();
    for (int i = 0; i < renderer.renderData.maxSamples; i++)
    {
        std::cout << "Sample " << i + 1 << "/" << renderer.renderData.maxSamples << std::endl;
        threads.startThreads(_nbThreads, renderer.renderData.chunkWidth, renderer.renderData.chunkHeight);

        while (1)
        {
            if (threads.getRemainingChunks() == 0)
            {
                break;
            }

            for (int x = 0; x < renderer.renderData.width; x++)
            {
                for (int y = 0; y < renderer.renderData.height; y++)
                {
                    raytracer::Color color = renderer.renderData.renderBuffer[x][y];
                    color = color * renderer.camera.sensitivity;
                    color.cap();
                    display.drawPixel(x, y, color);
                }
            }
            int event = display.getEvent();
            if (event == 1)
            {
                threads.stopThreads();
                display.endWindow();
                return;
            }
            display.displayScreen();
        }

        display.displayScreen();
        threads.stopThreads();

        renderer.stepMotions();
    }

    renderer.resetMotions();

    for (int x = 0; x < renderer.renderData.width; x++)
    {
        for (int y = 0; y < renderer.renderData.height; y++)
        {
            raytracer::Color color = renderer.renderData.renderBuffer[x][y];
            color = color * renderer.camera.sensitivity;
            color.cap();
            renderer.renderData.renderBuffer[x][y] = color;
            display.drawPixel(x, y, color);
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << "Rendered in " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "s" << std::endl;

    bool loop = true;
    while (loop)
    {

        int event = display.getEvent();
        if (event == 1)
        {
            loop = false;
        }
        display.displayScreen();
    }

    display.endWindow();
}

void raytracer::RenderProcessWrapper::renderImageCLI()
{
    auto begin = std::chrono::steady_clock::now();

    renderer.renderData.initRenderBuffer();
    renderer.initMotions();

    for (int i = 0; i < renderer.renderData.maxSamples; i++)
    {
        std::cout << "Sample " << i + 1 << "/" << renderer.renderData.maxSamples << std::endl;
        threads.startThreads(_nbThreads, renderer.renderData.chunkWidth, renderer.renderData.chunkHeight);

        while (1)
        {
            if (threads.getRemainingChunks() == 0)
            {
                break;
            }
        }

        threads.stopThreads();
        renderer.stepMotions();
    }

    renderer.resetMotions();

    for (int x = 0; x < renderer.renderData.width; x++)
    {
        for (int y = 0; y < renderer.renderData.height; y++)
        {
            raytracer::Color color = renderer.renderData.renderBuffer[x][y];
            color = color * renderer.camera.sensitivity;
            color.cap();
            renderer.renderData.renderBuffer[x][y] = color;
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << "Rendered in " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "s" << std::endl;
}
