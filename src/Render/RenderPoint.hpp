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

            bool hitObject(std::shared_ptr<IObject> object, Ray3D &ray);
            void hitNearestObject(const std::vector<std::shared_ptr<IObject>> &objects, Ray3D &ray);
            bool hits(const std::shared_ptr<IObject> &object, const Ray3D &ray) const;
            bool hitsSomething(const std::vector<std::shared_ptr<IObject>> &objects, const Ray3D &ray) const;

            std::shared_ptr<IObject> object;
            Vector3D surfaceNormal;
            Vector3D volumeNormal;
            Ray3D ray;
            Point3D hitPoint;
            double distance;
    };
}
