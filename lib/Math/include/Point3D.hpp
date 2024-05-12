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
#include "Matrix.hpp"

namespace raytracer
{
    class Point3D
    {
        public:
            double x, y, z;

            Point3D(double x = 0, double y = 0, double z = 0);
            Point3D(const Point3D &other);
            Point3D(Point3D&& other);
            Point3D(Vector3D vector3D);

            Point3D& operator=(const Point3D &other);

            friend std::ostream& operator<<(std::ostream& os, const Point3D& p);

            Point3D operator+(const Vector3D& vector) const;
            Point3D operator-(const Vector3D& vector) const;
            Vector3D operator-(const Point3D& other) const;
            bool operator==(const Point3D& other) const;

            static double distance(Point3D a, Point3D b);
            static Point3D rotateAroundCenter(Point3D &point, Point3D &center, double rx, double ry, double rz);
    };
}
