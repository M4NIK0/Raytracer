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

            Point3D(double x = 0, double y = 0, double z = 0);
            Point3D(const Point3D &other);
            Point3D(Point3D&& other);
            Point3D(Vector3D vector3D);

            virtual Point3D& operator=(const Point3D &other) = 0;

            friend std::ostream& operator<<(std::ostream& os, const Point3D& p);

            virtual Point3D operator+(const Vector3D& vector) = 0;
            virtual Point3D operator-(const Vector3D& vector) = 0;
            virtual Vector3D operator-(const Point3D& other) = 0;
            virtual bool operator==(const Point3D& other) = 0;

            static double distance(Point3D a, Point3D b);
            static Point3D rotateAroundCenter(Point3D &point, Point3D &center, double rx, double ry, double rz);
    };
}
