/*
** EPITECH PROJECT, 2024
** ILight.hpp
** File description:
** raytracer
*/

#pragma once

#include "../sfml/sfml.hpp"
#include "../Math/Point3D.hpp"
#include "../Math/Ray3D.hpp"

namespace raytracer
{
    class ILight
    {
        public:
            ~ILight() = default;

            virtual Color getColor() = 0;
            virtual double getIntensity() = 0;

            virtual std::vector<Ray3D> getLightRays(const Point3D &hitPoint) = 0;
            virtual double getIntensityFromDistance(double distance) = 0;
            virtual Point3D getPosition() = 0;

            virtual void setPosition(const Point3D &position) = 0;
            virtual void move(Vector3D vec) = 0;
    };
}
