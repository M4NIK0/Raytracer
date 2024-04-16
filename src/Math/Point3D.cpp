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
