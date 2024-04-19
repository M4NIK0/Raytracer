/*
** EPITECH PROJECT, 2024
** Rectangle3D.cpp
** File description:
** raytracer
*/

#include "Rectangle3D.hpp"

raytracer::Rectangle3D::~Rectangle3D() = default;

raytracer::Point3D raytracer::Rectangle3D::pointAt(double u, double v) const
{
    return origin + bottom_side * u + left_side * v;
}

void raytracer::Rectangle3D::move(raytracer::Vector3D direction)
{
    // move cam taking into account the rotation
    origin = origin + direction;
    bottom_side = bottom_side + direction;
}
