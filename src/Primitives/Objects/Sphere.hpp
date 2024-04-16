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
            Sphere(raytracer::Point3D pos, double r, Color color) : radius(r), position(pos), color(color) {}
            ~Sphere();

            bool hits(const Ray3D &ray) override;
            Point3D hitPosition(const Ray3D &ray) override;
            Vector3D hitNormal(const Ray3D &ray) override;
            Ray3D hitReflectedRay(const Ray3D &ray) override;
            void move(Vector3D vec) override;
            Color getColor() override { return color; }
            double getReflexionIndice(const Ray3D &ray) override { return 0.5; }

            double radius;
            Point3D position;
            Color color;
    };
}
