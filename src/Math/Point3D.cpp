/*
** EPITECH PROJECT, 2024
** Point3D.cpp
** File description:
** raytracer
*/

#include "Point3D.hpp"

raytracer::Point3D &raytracer::Point3D::operator=(const raytracer::Point3D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

raytracer::Point3D::Point3D(raytracer::Vector3D vector3D)
{
    x = vector3D.x;
    y = vector3D.y;
    z = vector3D.z;
}
