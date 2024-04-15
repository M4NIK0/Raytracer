/*
** EPITECH PROJECT, 2024
** Vector3D.hpp
** File description:
** raytracer
*/

#pragma once

namespace raytracer
{
    class Vector3D
    {
        public:
            Vector3D(double x = 0, double y = 0, double z = 0);

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

            double x = 0;
            double y = 0;
            double z = 0;
    };
}
