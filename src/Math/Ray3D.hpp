/*
** EPITECH PROJECT, 2024
** Ray3D.hpp
** File description:
** raytracer
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace raytracer
{
    class Ray3D
    {
        public:
            Ray3D() = default;
            Ray3D(const Point3D &origin, const Vector3D &direction) : origin(origin), direction(direction) {};
            ~Ray3D();

            Ray3D& operator=(Ray3D&& other) { // Move assignment operator
                if (this == &other) { return *this; }
                origin = std::move(other.origin);
                direction = std::move(other.direction);
                return *this;
            }

            Ray3D& operator=(const Ray3D& other) { // Copy assignment operator
                if (this == &other) { return *this; }
                origin = other.origin;
                direction = other.direction;
                return *this;
            }

            Point3D origin;
            Vector3D direction;
    };
}
