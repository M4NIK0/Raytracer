/*
** EPITECH PROJECT, 2024
** Sphere.cpp
** File description:
** raytracer
*/

#include "Sphere.hpp"

raytracer::Sphere::~Sphere() = default;

bool raytracer::Sphere::hits(const raytracer::Ray3D &ray)
{
    Vector3D oc = ray.origin - position;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}
