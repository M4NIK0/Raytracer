/*
** EPITECH PROJECT, 2024
** Triangle.cpp
** File description:
** raytracer
*/

#include "Triangle.hpp"

raytracer::Triangle::Triangle() = default;

raytracer::Triangle::~Triangle() = default;

raytracer::Point3D raytracer::Triangle::hit(const Ray3D &ray)
{
    Vector3D edge1 = _b - _a;
    Vector3D edge2 = _c - _a;
    Vector3D h = ray.direction.cross(edge2);
    double a = edge1.dot(h);

    if (a > -0.00001 && a < 0.00001)
        return {INFINITY, INFINITY, INFINITY};
    double f = 1 / a;
    Vector3D s = ray.origin - _a;
    double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return {INFINITY, INFINITY, INFINITY};
    Vector3D q = s.cross(edge1);
    double v = f * ray.direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
        return {INFINITY, INFINITY, INFINITY};
    double t = f * edge2.dot(q);
    if (t > 0.00001)
        return ray.origin + ray.direction * t;
    return {INFINITY, INFINITY, INFINITY};
}

raytracer::Vector3D raytracer::Triangle::getSurfaceNormal(const raytracer::Point3D &point)
{
    Vector3D edge1 = _b - _a;
    Vector3D edge2 = _c - _a;
    return edge1.cross(edge2).normalize();
}

raytracer::Vector3D raytracer::Triangle::getVolumeNormal(const raytracer::Point3D &point)
{
    return getSurfaceNormal(point);
}

raytracer::Color raytracer::Triangle::getSurfaceAbsorbtion(const raytracer::Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::Triangle::getSurfaceRoughness(const raytracer::Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::Triangle::getSurfaceTransparency(const raytracer::Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::Triangle::getSurfaceEmission(const raytracer::Point3D &point)
{
    return _emissionColor;
}

double raytracer::Triangle::getSurfaceEmissionIntensity(const raytracer::Point3D &point)
{
    return _emissionIntensity;
}

raytracer::Color raytracer::Triangle::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::Triangle::getVolumeAbsorbtionCoeff()
{
    return 0;
}

void raytracer::Triangle::move(raytracer::Vector3D vec)
{
    _a = _a + vec;
    _b = _b + vec;
    _c = _c + vec;
}

void raytracer::Triangle::rotate(raytracer::Vector3D vec)
{
}

bool raytracer::Triangle::getGlassState(const raytracer::Point3D &point)
{
    return _glassState;
}

double raytracer::Triangle::getRefractionIndex()
{
    return _refractionIndex;
}

double raytracer::Triangle::getReflexionIndex(const raytracer::Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::Triangle::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::Triangle::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::Triangle::setGlassState(bool state)
{
    _glassState = state;
}

void raytracer::Triangle::setSurfaceEmission(raytracer::Color color)
{
    _emissionColor = color;
}

void raytracer::Triangle::setSurfaceEmissionIntensity(double intensity)
{
    _emissionIntensity = intensity;
}

void raytracer::Triangle::setMotion(raytracer::Vector3D &translation, raytracer::Vector3D &rotation)
{
    _translation = translation;
    _rotation = rotation;
}

void raytracer::Triangle::initiateMotion(double time, size_t steps)
{
    _translationStep = _translation / static_cast<double>(steps);
    _rotationStep = _rotation / static_cast<double>(steps);
}

void raytracer::Triangle::resetMotion()
{
    _a = _aBackup;
    _b = _bBackup;
    _c = _cBackup;
}

void raytracer::Triangle::stepMotion()
{
    _a = _a + _translationStep;
    _b = _b + _translationStep;
    _c = _c + _translationStep;
}
