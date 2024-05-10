/*
** EPITECH PROJECT, 2024
** Sphere.cpp
** File description:
** raytracer
*/

#include <iostream>
#include "Plane.hpp"

raytracer::Plane::~Plane() = default;

raytracer::Point3D raytracer::Plane::hit(const Ray3D &ray)
{
    double t = (_position - ray.origin).dot(_normal) / ray.direction.dot(_normal);

    if (t < 0) {
        return {INFINITY, INFINITY, INFINITY};
    } else {
        return ray.origin + ray.direction * t;
    }
}

raytracer::Vector3D raytracer::Plane::getSurfaceNormal(const Point3D &point)
{
    return _normal;
}

raytracer::Vector3D raytracer::Plane::getVolumeNormal(const Point3D &point)
{
    return _normal;
}

raytracer::Color raytracer::Plane::getSurfaceAbsorbtion(const Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::Plane::getSurfaceRoughness(const Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::Plane::getSurfaceTransparency(const Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::Plane::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::Plane::getVolumeAbsorbtionCoeff()
{
    return _volumeAbsorbtionCoeff;
}

raytracer::Color raytracer::Plane::getSurfaceEmission(const Point3D &point)
{
    return _emissionColor;
}

double raytracer::Plane::getSurfaceEmissionIntensity(const Point3D &point)
{
    return _emissionIntensity;
}

void raytracer::Plane::move(Vector3D vec)
{
    _position = _position + vec;
    _positionBackup = _position;
}

void raytracer::Plane::rotate(Vector3D vec)
{
}

bool raytracer::Plane::getGlassState(const Point3D &point)
{
    return _isGlass;
}

double raytracer::Plane::getRefractionIndex()
{
    return _refractionIndex;
}

double raytracer::Plane::getReflexionIndex(const Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::Plane::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::Plane::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::Plane::setGlassState(bool state)
{
    _isGlass = state;
}

void raytracer::Plane::setSurfaceEmission(raytracer::Color color)
{
    _emissionColor = color;
}

void raytracer::Plane::setSurfaceEmissionIntensity(double intensity)
{
    _emissionIntensity = intensity;
}

void raytracer::Plane::setMotion(Vector3D &translation, Vector3D &rotation)
{
    _translation = translation;
    _rotation = rotation;
}

void raytracer::Plane::initiateMotion(double time, size_t steps)
{
    Vector3D totalTranslation = _translation * time;
    Vector3D totalRotation = _rotation * time;

    _translationStep = totalTranslation / steps;
    _rotationStep = totalRotation / steps;

    _position = _position - totalTranslation / 2;
    _rotation = _rotation - totalRotation / 2;
}

void raytracer::Plane::resetMotion()
{
    _position = _positionBackup;
}

void raytracer::Plane::stepMotion()
{
    _position = _position + _translationStep;
    _rotation = _rotation + _rotationStep;
}

raytracer::Point3D raytracer::Plane::getCenter() const
{
    return _position;
}

void raytracer::Plane::parseData(libconfig::Setting &config)
{
}
