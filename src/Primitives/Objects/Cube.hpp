/*
** EPITECH PROJECT, 2024
** Cube.hpp
** File description:
** raytracer
*/

#pragma once

#include "../IPrimitive.hpp"

namespace raytracer
{
    class Cube : public IPrimitive
    {
        public:
            Cube();
            ~Cube();

            bool hits(const raytracer::Ray3D &ray) override;
            Point3D hitPosition(const Ray3D &ray) override;
            Vector3D hitNormal(const Ray3D &ray) override;
            Ray3D hitReflectedRay(const Ray3D &ray) override;
            void move(Vector3D vec) override;
            Color getColor() override { return color; }

        private:
            Point3D _center;
            double _size;
            Color color;
    };
}
