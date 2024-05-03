/*
** EPITECH PROJECT, 2024
** Chunk.hpp
** File description:
** raytracer
*/

#pragma once

#include <cstddef>

namespace raytracer
{
    class Chunk
    {
        public:
            Chunk(size_t x, size_t y, size_t width, size_t height) : x(x), y(y), width(width), height(height) {}
            ~Chunk() = default;

            size_t x;
            size_t y;

            size_t width;
            size_t height;
    };
}
