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
            RenderProcessWrapper(Renderer &rd, size_t nbThreads);
            ~RenderProcessWrapper();

            void renderImageDisplay(int windowSize = 800);

            void renderImageCLI();

            Renderer renderer;
            Threads threads;
            sfml display;

        private:
            int _width, _height;
            size_t _nbThreads;
    };
}
