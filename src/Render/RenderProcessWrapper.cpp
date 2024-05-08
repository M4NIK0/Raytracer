/*
** EPITECH PROJECT, 2024
** RenderProcessWrapper.cpp
** File description:
** raytracer
*/

#include "RenderProcessWrapper.hpp"

raytracer::RenderProcessWrapper::RenderProcessWrapper(int width, int height, size_t nbThreads): renderer(Renderer(Camera(width, height))), threads(Threads(renderer)), _width(width), _height(height), _nbThreads(nbThreads)
{
    renderer.renderData.width = width;
    renderer.renderData.height = height;

    renderer.renderData.initRenderBuffer();
}

raytracer::RenderProcessWrapper::~RenderProcessWrapper() = default;

void raytracer::RenderProcessWrapper::renderImageDisplay(int windowSize)
{
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
