/*
** EPITECH PROJECT, 2024
** Vector3D.cpp
** File description:
** raytracer
*/

#include "../include/Vector3D.hpp"

raytracer::Vector3D raytracer::Vector3D::operator+(const raytracer::Vector3D &other) const
{
    return raytracer::Vector3D();
}

raytracer::Vector3D &raytracer::Vector3D::operator+=(const raytracer::Vector3D &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

raytracer::Vector3D raytracer::Vector3D::operator-(const raytracer::Vector3D &other) const
{
    Vector3D result = *this;
    result -= other;
    return result;
}

raytracer::Vector3D &raytracer::Vector3D::operator-=(const raytracer::Vector3D &other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *this;
}

raytracer::Vector3D raytracer::Vector3D::operator*(const raytracer::Vector3D &other) const
{
    return Vector3D(x * other.x, y * other.y, z * other.z);
}

raytracer::Vector3D &raytracer::Vector3D::operator*=(const raytracer::Vector3D &other)
{
    x *= other.x; y *= other.y; z *= other.z;

    return *this;
}

raytracer::Vector3D raytracer::Vector3D::operator/(const raytracer::Vector3D &other) const
{
    return Vector3D(x / other.x, y / other.y, z / other.z);
}

raytracer::Vector3D &raytracer::Vector3D::operator/=(const raytracer::Vector3D &other)
{
    x /= other.x; y /= other.y; z /= other.z;
    return *this;
}

raytracer::Vector3D raytracer::Vector3D::operator*(double scalar) const
{
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

raytracer::Vector3D &raytracer::Vector3D::operator*=(double scalar)
{
    x *= scalar; y *= scalar; z *= scalar;
    return *this;
}

raytracer::Vector3D raytracer::Vector3D::operator/(double scalar) const
{
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

raytracer::Vector3D &raytracer::Vector3D::operator/=(double scalar)
{
    x /= scalar; y /= scalar; z /= scalar;
    return *this;
}

double raytracer::Vector3D::length() const
{
    return std::sqrt(x*x + y*y + z*z);
}

double raytracer::Vector3D::dot(const raytracer::Vector3D &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

raytracer::Vector3D raytracer::Vector3D::cross(const raytracer::Vector3D &other) const
{
    return Vector3D(y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x);
}

raytracer::Vector3D raytracer::Vector3D::normalize()
{
    double len = length();
    if (len == 0)
        return *this;

    return Vector3D(x / len, y / len, z / len);
}
