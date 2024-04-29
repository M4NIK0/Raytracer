/*
** EPITECH PROJECT, 2024
** RenderPoint.hpp
** File description:
** raytracer
*/

#pragma once

#include "../sfml/sfml.hpp"
#include "../Math/Point3D.hpp"
#include "../Math/Ray3D.hpp"
#include "../Primitives/IPrimitive.hpp"

namespace raytracer
{
    class RenderPoint
    {
        public:
            RenderPoint();

            ~RenderPoint();

            std::shared_ptr<IPrimitive> object;
            Vector3D surfaceNormal;
            Ray3D ray;
            Point3D hitPoint;
    };
}
