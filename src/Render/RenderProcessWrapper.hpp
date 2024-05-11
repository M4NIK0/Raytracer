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

            void initCamera(int sensibility, int exposure, Point3D position, Vector3D rotation)
            {
                Camera camera(_width, _height);
                camera.sensitivity = sensibility;
                camera.exposure = exposure;

                renderer.camera = camera;
                renderer.camera.move(Vector3D(position.x, position.y, position.z));
                renderer.camera.rotate(Vector3D(rotation.x, rotation.y, rotation.z));
            }

            void initRenderData(int chunkSizeX, int chunkSizeY, int maxSamples)
            {
                renderer.renderData.chunkWidth = chunkSizeX;
                renderer.renderData.chunkHeight = chunkSizeY;
                renderer.renderData.maxSamples = maxSamples;
            }

            void addObject(std::shared_ptr<IObject> object)
            {
                renderer.addObject(object);
            }

            void addLight(std::shared_ptr<ILight> light)
            {
                renderer.addLight(light);
            }

            raytracer::Color getPixelColor(int x, int y)
            {
                return renderer.renderData.renderBuffer[x][y];
            }

        private:
            Renderer renderer;
            Threads threads;
            sfml display;

            int _width, _height;
            size_t _nbThreads;
    };
}
