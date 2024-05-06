/*
** EPITECH PROJECT, 2024
** Sphere.cpp
** File description:
** raytracer
*/

#include <iostream>
#include "Sphere.hpp"

raytracer::Sphere::~Sphere() = default;

raytracer::Point3D raytracer::Sphere::hit(const Ray3D &ray)
{
    Vector3D oc = ray.
    origin - _position;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return Point3D(INFINITY, INFINITY, INFINITY);
    } else {
        double root1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

        if (root1 > 0) {
            return ray.origin + ray.direction * root1;
        } else if (root2 > 0) {
            return ray.origin + ray.direction * root2;
        } else {
            return Point3D(INFINITY, INFINITY, INFINITY);
        }
    }
}

raytracer::Vector3D raytracer::Sphere::getSurfaceNormal(const Point3D &point)
{
    return (point - _position).normalize();
}

raytracer::Vector3D raytracer::Sphere::getVolumeNormal(const Point3D &point)
{
    return (point - _position).normalize();
}

raytracer::Color raytracer::Sphere::getSurfaceAbsorbtion(const Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::Sphere::getSurfaceRoughness(const Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::Sphere::getSurfaceTransparency(const Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::Sphere::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::Sphere::getVolumeAbsorbtionCoeff()
{
    return _volumeAbsorbtionCoeff;
}

void raytracer::Sphere::move(Vector3D vec)
{
    _position = _position + vec;
}

void raytracer::Sphere::rotate(Vector3D vec)
{
}

bool raytracer::Sphere::getGlassState(const Point3D &point)
{
    return _isGlass;
}

double raytracer::Sphere::getRefractionIndex()
{
    return _refractionIndex;
}

double raytracer::Sphere::getReflexionIndex(const Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::Sphere::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::Sphere::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::Sphere::setGlassState(bool state)
{
    _isGlass = state;
}

void raytracer::Sphere::setMotion(Vector3D &translation, Vector3D &rotation)
{
    _translation = translation;
    _rotation = rotation;
}
