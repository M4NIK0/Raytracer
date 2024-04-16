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

            bool hits(const Ray3D &ray) override;
            Point3D hitPosition(const Ray3D &ray) override;
            Vector3D hitNormal(const Ray3D &ray) override;
            Ray3D hitReflectedRay(const Ray3D &ray) override;

            double radius;
            Point3D position;
    };
}
