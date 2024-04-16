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

            friend std::ostream& operator<<(std::ostream& os, const Ray3D& r) { os << "Ray3D(" << r.origin << ", " << r.direction << ")"; return os; }

            Ray3D& operator=(const Ray3D& other);

            Point3D origin;
            Vector3D direction;
    };
}
