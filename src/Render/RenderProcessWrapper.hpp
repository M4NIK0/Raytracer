/*
** EPITECH PROJECT, 2024
** RenderProcessWrapper.hpp
** File description:
** raytracer
*/

#pragma once

#include "Renderer.hpp"
#include "Threads.hpp"
#include "../sfml/sfml.hpp"

namespace raytracer
{
    class RenderProcessWrapper
    {
        public:
            RenderProcessWrapper(int width = 800, int height = 600, size_t nbThreads = 1);
            ~RenderProcessWrapper();

            void renderImageDisplay(int windowSize = 800);
            void renderImageCLI();

            // Mediator methods
            void startThreads();
            void stopThreads();
            void initMotions();
            void stepMotions();
            void resetMotions();
            void drawPixel(int x, int y, Color color);
            void displayScreen();
            void endWindow();

            void initCamera(int sensibility, int exposure, Point3D position, Vector3D rotation);

            void initRenderData(int chunkSizeX, int chunkSizeY, int maxSamples);

            void addObject(std::shared_ptr<IObject> object);

            void addLight(std::shared_ptr<ILight> light);

            raytracer::Color getPixelColor(int x, int y);

        private:
            Renderer renderer;
            Threads threads;
            sfml display;

            int _width, _height;
            size_t _nbThreads;
    };
}
