/*
** EPITECH PROJECT, 2024
** RenderData.hpp
** File description:
** raytracer
*/

#pragma once

#include <vector>
#include <memory>
#include "../Light/ILight.hpp"
#include "../Objects/IObject.hpp"

namespace raytracer
{
    class RenderData
    {
        public:
            RenderData() = default;
            ~RenderData() = default;

            void initRenderBuffer();

            std::vector<std::shared_ptr<IObject>> objects = {};
            std::vector<std::shared_ptr<ILight>> lights = {};

            size_t diffuseRays = 2;
            size_t reflexionsRays = 5;
            size_t maxBounces = 2;

            std::vector<std::vector<Color>> renderBuffer = {};

            int width = 1920;
            int height = 1080;

            int chunkWidth = 100;
            int chunkHeight = 100;

            int maxSamples = 5;
    };
}
