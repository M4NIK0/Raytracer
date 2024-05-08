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
            RenderProcessWrapper(int width, int height);
            ~RenderProcessWrapper();

            Renderer renderer;
            Threads threads;
            sfml display;
    };
}
