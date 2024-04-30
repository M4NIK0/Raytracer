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
#include "../Objects/IObject.hpp"

namespace raytracer
{
    class RenderPoint
    {
        public:
            RenderPoint();

            ~RenderPoint();

            std::shared_ptr<IObject> object;
            Vector3D surfaceNormal;
            Vector3D volumeNormal;
            Ray3D ray;
            Point3D hitPoint;
    };
}
