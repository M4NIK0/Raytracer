/*
** EPITECH PROJECT, 2024
** Sphere.hpp
** File description:
** raytracer
*/

#pragma once

#include "../IPrimitive.hpp"

namespace raytracer
{
    class Sphere : public IPrimitive
    {
        public:
            Sphere(raytracer::Point3D pos, double r = 0) : radius(r), position(pos) {}
            ~Sphere();

            bool hits(const raytracer::Ray3D &ray) override;

            double radius;
            Point3D position;
    };
}
