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
            RenderProcessWrapper(int width, int height, int windowSize = 800);
            ~RenderProcessWrapper();

            void renderImageDisplay();

            void renderImageCLI();

            Renderer renderer;
            Threads threads;
            sfml display;
    };
}
