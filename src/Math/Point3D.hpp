/*
** EPITECH PROJECT, 2024
** Point3D.hpp
** File description:
** raytracer
*/

#pragma once

#include <utility>
#include "Vector3D.hpp"

namespace raytracer
{
    class Point3D
    {
        public:
            double x, y, z;

            Point3D(double x = 0, double y = 0, double z = 0) : x(0), y(0), z(0) {};
            Point3D(const Point3D &other) : x(other.x), y(other.y), z(other.z) {};
            Point3D(Point3D&& other) : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)) {};

            Point3D& operator=(const Point3D &other) {
                if (this == &other) { return *this; }
                x = other.x;
                y = other.y;
                z = other.z;
            }

            Point3D& operator=(Point3D&& other) {
                if (this == &other) { return *this; }
                x = std::move(other.x);
                y = std::move(other.y);
                z = std::move(other.z);
            }

            Point3D operator+(const Vector3D& vector) const { return Point3D(x + vector.x, y + vector.y, z + vector.z); }
            Vector3D operator-(const Point3D& other) const { return Vector3D(x - other.x, y - other.y, z - other.z); }
    };
}
