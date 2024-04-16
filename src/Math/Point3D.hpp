/*
** EPITECH PROJECT, 2024
** Point3D.hpp
** File description:
** raytracer
*/

#pragma once

#include <utility>
#include <iostream>
#include "Vector3D.hpp"

namespace raytracer
{
    class Point3D
    {
        public:
            double x, y, z;

            Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {};
            Point3D(const Point3D &other) : x(other.x), y(other.y), z(other.z) {};
            Point3D(Point3D&& other) : x(other.x), y(other.y), z(other.z) {};

            Point3D& operator=(const Point3D &other);

            friend std::ostream& operator<<(std::ostream& os, const Point3D& p) { os << "Point3D(" << p.x << ", " << p.y << ", " << p.z << ")"; return os; }

            Point3D operator+(const Vector3D& vector) const { return Point3D(x + vector.x, y + vector.y, z + vector.z); }
            Vector3D operator-(const Point3D& other) const { return Vector3D(x - other.x, y - other.y, z - other.z); }

            static double distance(Point3D a, Point3D b) { return (a - b).length(); }
    };
}
