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
            Sphere(double r = 0, Point3D pos = Point3D(0, 0, 0)) : radius(r), position(pos) {}
            ~Sphere();

            bool hits(const raytracer::Ray3D &ray) override;

            double radius;
            Point3D position;
    };
}
