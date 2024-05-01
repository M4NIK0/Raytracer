/*
** EPITECH PROJECT, 2024
** Cube.cpp
** File description:
** raytracer
*/

#include "Cube.hpp"

raytracer::Cube::~Cube() = default;

raytracer::Point3D raytracer::Cube::hit(const Ray3D &ray)
{
    double tmin = (_position.x - _sideLength / 2 - ray.origin.x) / ray.direction.x;
    double tmax = (_position.x + _sideLength / 2 - ray.origin.x) / ray.direction.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    double tymin = (_position.y - _sideLength / 2 - ray.origin.y) / ray.direction.y;
    double tymax = (_position.y + _sideLength / 2 - ray.origin.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return Point3D(INFINITY, INFINITY, INFINITY);
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    double tzmin = (_position.z - _sideLength / 2 - ray.origin.z) / ray.direction.z;
    double tzmax = (_position.z + _sideLength / 2 - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return Point3D(INFINITY, INFINITY, INFINITY);
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return ray.origin + ray.direction * tmin;
}

raytracer::Vector3D raytracer::Cube::getSurfaceNormal(const Point3D &point)
{
    Vector3D normal;
    Point3D center = _position + Vector3D(_sideLength / 2, _sideLength / 2, _sideLength / 2);

    if (std::abs(point.x - center.x) > _sideLength / 2)
        normal.x = (point.x - center.x > 0) ? 1 : -1;
    if (std::abs(point.y - center.y) > _sideLength / 2)
        normal.y = (point.y - center.y > 0) ? 1 : -1;
    if (std::abs(point.z - center.z) > _sideLength / 2)
        normal.z = (point.z - center.z > 0) ? 1 : -1;

    return normal.normalize();
}

raytracer::Vector3D raytracer::Cube::getVolumeNormal(const Point3D &point)
{
    return getSurfaceNormal(point);
}
raytracer::Color raytracer::Cube::getSurfaceAbsorbtion(const Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::Cube::getSurfaceRoughness(const Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::Cube::getSurfaceTransparency(const Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::Cube::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::Cube::getVolumeAbsorbtionCoeff()
{
    return _volumeAbsorbtionCoeff;
}

void raytracer::Cube::move(Vector3D vec)
{
    _position = _position + vec;
}

void raytracer::Cube::rotate(Vector3D vec)
{
}

bool raytracer::Cube::getGlassState(const Point3D &point)
{
    return _isGlass;
}

double raytracer::Cube::getRefractionxionIndex()
{
    return _refractionIndex;
}

double raytracer::Cube::getReflexionIndex(const Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::Cube::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::Cube::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::Cube::setGlassState(bool state)
{
    _isGlass = state;
}