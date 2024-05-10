/*
** EPITECH PROJECT, 2024
** Vector3D.cpp
** File description:
** raytracer
*/

#include "Vector3D.hpp"

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
