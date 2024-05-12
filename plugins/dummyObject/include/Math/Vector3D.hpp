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

            Vector3D operator+(const Vector3D& other) const { return Vector3D(x + other.x, y + other.y, z + other.z); }
            Vector3D& operator+=(const Vector3D& other) { x += other.x; y += other.y; z += other.z; return *this; }
            Vector3D operator-(const Vector3D& other) const { return Vector3D(x - other.x, y - other.y, z - other.z); }
            Vector3D& operator-=(const Vector3D& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
            Vector3D operator*(const Vector3D& other) const { return Vector3D(x * other.x, y * other.y, z * other.z); }
            Vector3D& operator*=(const Vector3D& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
            Vector3D operator/(const Vector3D& other) const { return Vector3D(x / other.x, y / other.y, z / other.z); }
            Vector3D& operator/=(const Vector3D& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

            Vector3D operator*(double scalar) const { return Vector3D(x * scalar, y * scalar, z * scalar); }
            Vector3D& operator*=(double scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
            Vector3D operator/(double scalar) const { return Vector3D(x / scalar, y / scalar, z / scalar); }
            Vector3D& operator/=(double scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

            double length() const { return std::sqrt(x*x + y*y + z*z); }

            double dot(const Vector3D& other) const { return x * other.x + y * other.y + z * other.z; }

            Vector3D cross(const Vector3D &other) const;

            Vector3D normalize();


            double x = 0;
            double y = 0;
            double z = 0;

            friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) { os << "Vector3D(" << v.x << ", " << v.y << ", " << v.z << ")"; return os;}
    };
}
