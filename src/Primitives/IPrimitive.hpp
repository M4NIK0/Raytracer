/*
** EPITECH PROJECT, 2024
** IPrimitive.hpp
** File description:
** raytracer
*/

#pragma once

#include "../Math/Ray3D.hpp"

namespace raytracer
{
    class IPrimitive
    {
        public:
            virtual ~IPrimitive() = default;

            virtual bool hits(const raytracer::Ray3D &ray) = 0;
    };
}
