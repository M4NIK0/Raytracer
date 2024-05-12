/*
** EPITECH PROJECT, 2024
** Vector3D.hpp
** File description:
** raytracer
*/

#pragma once

#include <cmath>
#include <iostream>

namespace raytracer
{
    class Vector3D
    {
        public:
            Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

            Vector3D operator+(const Vector3D& other) const;
            Vector3D& operator+=(const Vector3D& other);
            Vector3D operator-(const Vector3D& other) const;
            Vector3D& operator-=(const Vector3D& other);
            Vector3D operator*(const Vector3D& other) const;
            Vector3D& operator*=(const Vector3D& other);
            Vector3D operator/(const Vector3D& other) const;
            Vector3D& operator/=(const Vector3D& other);

            Vector3D operator*(double scalar) const;
            Vector3D& operator*=(double scalar);
            Vector3D operator/(double scalar) const;
            Vector3D& operator/=(double scalar);

            double length() const;

            double dot(const Vector3D& other) const;

            Vector3D cross(const Vector3D &other) const;

            Vector3D normalize();


            double x = 0;
            double y = 0;
            double z = 0;

            friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) { os << "Vector3D(" << v.x << ", " << v.y << ", " << v.z << ")"; return os;}
    };
}
