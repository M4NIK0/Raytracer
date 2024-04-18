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

raytracer::Point3D raytracer::Sphere::hitPosition(const raytracer::Ray3D &ray)
{
    Vector3D oc = ray.
    origin - position;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return Point3D(0, 0, 0);
    } else {
        double root1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

        if (root1 > 0) {
            return ray.origin + ray.direction * root1;
        } else if (root2 > 0) {
            return ray.origin + ray.direction * root2;
        } else {
            return Point3D(0, 0, 0);
        }
    }
}

raytracer::Vector3D raytracer::Sphere::hitNormal(const raytracer::Ray3D &ray)
{
    return (hitPosition(ray) - position);
}

raytracer::Ray3D raytracer::Sphere::hitReflectedRay(const raytracer::Ray3D &ray)
{
    Vector3D oc = ray.origin - position;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return {};
    } else {
        double root1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

        if (root1 > 0) {
            Point3D hitPos = ray.origin + ray.direction * root1;
            Vector3D normal = (hitPos - position).normalize();
            Vector3D reflectedDirection = ray.direction - normal * 2.0 * ray.direction.dot(normal);
            return Ray3D(hitPos, reflectedDirection);
        } else if (root2 > 0) {
            Point3D hitPos = ray.origin + ray.direction * root2;
            Vector3D normal = (hitPos - position).normalize();
            Vector3D reflectedDirection = ray.direction - normal * 2.0 * ray.direction.dot(normal);
            return Ray3D(hitPos, reflectedDirection);
        } else {
            return {};
        }
    }
}

void raytracer::Sphere::move(raytracer::Vector3D vec)
{
    position = position + vec;
}

raytracer::Vector3D raytracer::Sphere::getNormalFromPoint(const raytracer::Point3D &point)
{
    Vector3D normal = (point - position).normalize();

    return normal;
}
