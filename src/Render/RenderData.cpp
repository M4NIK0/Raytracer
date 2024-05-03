/*
** EPITECH PROJECT, 2024
** RenderData.cpp
** File description:
** raytracer
*/

#include "RenderData.hpp"

void raytracer::RenderData::initRenderBuffer()
{
    renderBuffer.clear();
    for (int i = 0; i < width; i++)
    {
        renderBuffer.emplace_back();
        for (int j = 0; j < height; j++)
        {
            renderBuffer[i].emplace_back(0, 0, 0);
        }
    }
}
