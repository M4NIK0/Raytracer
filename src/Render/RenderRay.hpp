/*
** EPITECH PROJECT, 2024
** RenderRay.hpp
** File description:
** raytracer
*/

#pragma once

#include "../Math/Ray3D.hpp"

namespace raytracer
{
    class RenderRay : public Ray3D
    {
        public:
            RenderRay(Point3D origin = {0, 0, 0}, Vector3D direction = {0, 0, 0});

            RenderRay(Ray3D ray) : Ray3D(ray.origin, ray.direction) {}

            ~RenderRay();

            Color getColor();

            RenderRay &operator=(const RenderRay &other)
            {
                origin = other.origin;
                direction = other.direction;
                color = other.color;
                intensity = other.intensity;
                return *this;
            }

            RenderRay &operator=(const Ray3D &other)
            {
                origin = other.origin;
                direction = other.direction;
                return *this;
            }

            RenderRay &operator+(const RenderRay &other)
            {
                color = color + other.color;
                intensity + other.intensity;
                return *this;
            }

            Ray3D getRay() { return Ray3D(origin, direction); }

            Color color = {0, 0, 0};
            double intensity = 0;
    };
}
