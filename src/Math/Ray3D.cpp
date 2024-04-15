/*
** EPITECH PROJECT, 2024
** Ray3D.cpp
** File description:
** raytracer
*/

#include "Ray3D.hpp"

raytracer::Ray3D::~Ray3D() = default;

raytracer::Ray3D &raytracer::Ray3D::operator=(const raytracer::Ray3D &other){
    if (this == &other) { return *this; }
    origin = other.origin;
    direction = other.direction;

    return *this;
}
