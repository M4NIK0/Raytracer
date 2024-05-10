/*
** EPITECH PROJECT, 2024
** Cylinder.cpp
** File description:
** raytracer
*/

#include <iostream>
#include "Cylinder.hpp"

raytracer::Cylinder::~Cylinder() = default;

raytracer::Point3D raytracer::Cylinder::hit(const Ray3D &ray)
{
    // Calculate coefficients for the quadratic equation
    Vector3D oc = ray.origin - _position;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - _radius*_radius;
    double discriminant = b*b - 4*a*c;

    // If discriminant is negative, there are no real roots
    if (discriminant < 0) return {INFINITY, INFINITY, INFINITY};

    // Compute q as described above
    double distSqrt = sqrt(discriminant);
    double q;
    if (b < 0) q = (-b - distSqrt)/2.0;
    else q = (-b + distSqrt)/2.0;

    // Compute t0 and t1
    double t0 = q / a;
    double t1 = c / q;

    // Make sure t0 is smaller than t1
    if (t0 > t1) std::swap(t0, t1);

    // If t1 is less than zero, the object is in the ray's negative direction
    if (t1 < 0) return {INFINITY, INFINITY, INFINITY};

    // If t0 is less than zero, the intersection point is at t1
    double t = t0 < 0 ? t1 : t0;

    // Calculate the intersection point
    Point3D intersection = ray.origin + ray.direction * t;

    // Check if the intersection point is within the bounds of the cylinder's height
    if (intersection.y < _position.y || intersection.y > _position.y + _height) {
        return {INFINITY, INFINITY, INFINITY};
    }

    // Check if the intersection point is within the radius of the cylinder at the intersection's height
    double distanceFromCenter = (intersection - _position).length();
    if (distanceFromCenter > _radius) {
        return {INFINITY, INFINITY, INFINITY};
    }

    return intersection;
}

raytracer::Vector3D raytracer::Cylinder::getSurfaceNormal(const Point3D &point)
{
    Vector3D cp = point - _position;
    return Vector3D(cp.x, 0, cp.z).normalize();
}

raytracer::Vector3D raytracer::Cylinder::getVolumeNormal(const Point3D &point)
{
    return getSurfaceNormal(point);
}

raytracer::Color raytracer::Cylinder::getSurfaceAbsorbtion(const Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::Cylinder::getSurfaceRoughness(const Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::Cylinder::getSurfaceTransparency(const Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::Cylinder::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::Cylinder::getVolumeAbsorbtionCoeff()
{
    return _volumeAbsorbtionCoeff;
}

raytracer::Color raytracer::Cylinder::getSurfaceEmission(const Point3D &point)
{
    return _emissionColor;
}

double raytracer::Cylinder::getSurfaceEmissionIntensity(const Point3D &point)
{
    return _emissionIntensity;
}

void raytracer::Cylinder::move(Vector3D vec)
{
    _position = _position + vec;
    _positionBackup = _position;
}

void raytracer::Cylinder::rotate(Vector3D vec)
{
}

bool raytracer::Cylinder::getGlassState(const Point3D &point)
{
    return _isGlass;
}

double raytracer::Cylinder::getRefractionIndex()
{
    return _refractionIndex;
}

double raytracer::Cylinder::getReflexionIndex(const Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::Cylinder::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::Cylinder::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::Cylinder::setGlassState(bool state)
{
    _isGlass = state;
}

void raytracer::Cylinder::setSurfaceEmission(raytracer::Color color)
{
    _emissionColor = color;
}

void raytracer::Cylinder::setSurfaceEmissionIntensity(double intensity)
{
    _emissionIntensity = intensity;
}

void raytracer::Cylinder::setMotion(Vector3D &translation, Vector3D &rotation)
{
    _translation = translation;
    _rotation = rotation;
}

void raytracer::Cylinder::initiateMotion(double time, size_t steps)
{
    Vector3D totalTranslation = _translation * time;
    Vector3D totalRotation = _rotation * time;

    _translationStep = totalTranslation / steps;
    _rotationStep = totalRotation / steps;

    _position = _position - totalTranslation / 2;
    _rotation = _rotation - totalRotation / 2;
}

void raytracer::Cylinder::resetMotion()
{
    _position = _positionBackup;
}

void raytracer::Cylinder::stepMotion()
{
    _position = _position + _translationStep;
    _rotation = _rotation + _rotationStep;
}

raytracer::Point3D raytracer::Cylinder::getCenter() const
{
    return _position;
}
