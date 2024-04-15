/*
** EPITECH PROJECT, 2024
** Sphere.cpp
** File description:
** raytracer
*/

#include <iostream>
#include "Sphere.hpp"

raytracer::Sphere::~Sphere() = default;

bool raytracer::Sphere::hits(const raytracer::Ray3D &ray)
{
    Vector3D oc = ray.origin - position;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    } else {
        double root1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

        // Check if the roots are positive
        if (root1 > 0 || root2 > 0) {
            return true;
        } else {
            return false;
        }
    }
}