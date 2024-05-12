/*
** EPITECH PROJECT, 2024
** Ray3D.cpp
** File description:
** raytracer
*/

#include "../include/Ray3D.hpp"

raytracer::Ray3D::Ray3D() = default;
raytracer::Ray3D::Ray3D(const raytracer::Point3D &origin, const raytracer::Vector3D &direction) : origin(origin), direction(direction) {}

raytracer::Ray3D::~Ray3D() = default;

std::ostream &raytracer::operator<<(std::ostream &os, const raytracer::Ray3D &r)
{
    os << "Ray3D(" << r.origin << ", " << r.direction << ")"; return os;
}

raytracer::Ray3D &raytracer::Ray3D::operator=(const raytracer::Ray3D &other){
    if (this == &other) { return *this; }
    origin = other.origin;
    direction = other.direction;

    return *this;
}
