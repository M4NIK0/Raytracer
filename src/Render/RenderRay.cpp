/*
** EPITECH PROJECT, 2024
** RenderRay.cpp
** File description:
** raytracer
*/

#include "RenderRay.hpp"

raytracer::RenderRay::RenderRay(Point3D origin, Vector3D direction) : Ray3D(origin, direction) {}

raytracer::RenderRay::~RenderRay() = default;

raytracer::Color raytracer::RenderRay::getColor()
{
    return color;
}
