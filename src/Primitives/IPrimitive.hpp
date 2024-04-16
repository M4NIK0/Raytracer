/*
** EPITECH PROJECT, 2024
** IPrimitive.hpp
** File description:
** raytracer
*/

#pragma once

#include "../Math/Ray3D.hpp"
#include "../sfml/sfml.hpp"

namespace raytracer
{
    class IPrimitive
    {
        public:
            virtual ~IPrimitive() = default;

            virtual bool hits(const raytracer::Ray3D &ray) = 0;
            virtual Point3D hitPosition(const Ray3D &ray) = 0;
            virtual Vector3D hitNormal(const Ray3D &ray) = 0;
            virtual Ray3D hitReflectedRay(const Ray3D &ray) = 0;
            virtual void move(Vector3D vec) = 0;
            virtual Color getColor() = 0;
    };
}
