/*
** EPITECH PROJECT, 2024
** Cube.cpp
** File description:
** raytracer
*/

#include "Cube.hpp"

raytracer::Cube::Cube() : _center(Point3D(0, 0, 0)), _size(1), color(Color(255, 255, 255))
{

}

raytracer::Cube::~Cube()
{

}

bool raytracer::Cube::hits(const raytracer::Ray3D &ray)
{
}

raytracer::Point3D raytracer::Cube::hitPosition(const raytracer::Ray3D &ray)
{

}

raytracer::Vector3D raytracer::Cube::hitNormal(const raytracer::Ray3D &ray)
{
}

raytracer::Ray3D raytracer::Cube::hitReflectedRay(const raytracer::Ray3D &ray)
{
}

void raytracer::Cube::move(raytracer::Vector3D vec)
{
    _center = _center + vec;
}
