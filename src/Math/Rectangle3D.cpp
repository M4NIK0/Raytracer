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
