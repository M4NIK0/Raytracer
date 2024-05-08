/*
** EPITECH PROJECT, 2024
** RenderProcessWrapper.cpp
** File description:
** raytracer
*/

#include "RenderProcessWrapper.hpp"

raytracer::RenderProcessWrapper::RenderProcessWrapper(int width, int height): renderer(Renderer(Camera(width, height))), threads(Threads(renderer)) {}

raytracer::RenderProcessWrapper::~RenderProcessWrapper() = default;
