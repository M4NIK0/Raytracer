/*
** EPITECH PROJECT, 2024
** Sphere.cpp
** File description:
** raytracer
*/

#include <iostream>
#include "Sphere.hpp"

raytracer::Sphere::Sphere() : _radius(1), _position(Point3D(0, 0, 0)), _surfaceRoughness(0),
                              _surfaceAbsorbtion(Color(1, 1, 1)), _volumeAbsorbtion(Color(0, 0, 0)), _volumeAbsorbtionCoeff(0),
                              _isGlass(false), _reflexionIndex(0), _refractionIndex(0), _translation(Vector3D(0, 0, 0)),
                              _rotation(Vector3D(0, 0, 0)) {}

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

raytracer::Color raytracer::Sphere::getSurfaceEmission(const Point3D &point)
{
    return _emissionColor;
}

double raytracer::Sphere::getSurfaceEmissionIntensity(const Point3D &point)
{
    return _emissionIntensity;
}

void raytracer::Sphere::move(Vector3D vec)
{
    _position = _position + vec;
    _positionBackup = _position;
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

void raytracer::Sphere::setSurfaceEmission(raytracer::Color color)
{
    _emissionColor = color;
}

void raytracer::Sphere::setSurfaceEmissionIntensity(double intensity)
{
    _emissionIntensity = intensity;
}

void raytracer::Sphere::setMotion(Vector3D &translation, Vector3D &rotation)
{
    _translation = translation;
    _rotation = rotation;
}

void raytracer::Sphere::initiateMotion(double time, size_t steps)
{
    Vector3D totalTranslation = _translation * time;
    Vector3D totalRotation = _rotation * time;

    _translationStep = totalTranslation / steps;
    _rotationStep = totalRotation / steps;

    _position = _position - totalTranslation / 2;
    _rotation = _rotation - totalRotation / 2;
}

void raytracer::Sphere::resetMotion()
{
    _position = _positionBackup;
}

void raytracer::Sphere::stepMotion()
{
    _position = _position + _translationStep;
    _rotation = _rotation + _rotationStep;
}

void raytracer::Sphere::parseData(libconfig::Setting &config)
{
    _radius = config["radius"];
    if (_radius <= 0)
        throw Error("Radius must be > 0");
    libconfig::Setting& position = config["position"];
    _position.x = position[0];
    _position.y = position[1];
    _position.z = position[2];
    _reflexionIndex = config["reflexion"];
    if (_reflexionIndex < 0 || _reflexionIndex > 1)
        throw Error("Reflexion must be between 0 and 1");
    _surfaceRoughness = config["roughness"];
    if (_surfaceRoughness < 0 || _surfaceRoughness > 1)
        throw Error("Roughness must be between 0 and 1");
    libconfig::Setting& color = config["color"];
    _surfaceAbsorbtion.r = (255.0 - (double)color[0]) / 255.0;
    _surfaceAbsorbtion.g = (255.0 - (double)color[1]) / 255.0;
    _surfaceAbsorbtion.b = (255.0 - (double)color[2]) / 255.0;
    if (_surfaceAbsorbtion.r < 0 || _surfaceAbsorbtion.r > 1 || _surfaceAbsorbtion.g < 0 || _surfaceAbsorbtion.g > 1 || _surfaceAbsorbtion.b < 0 || _surfaceAbsorbtion.b > 1)
        throw Error("color must be between 0 & 255");
    _isGlass = config["glass"];
    if (_isGlass) {
        _refractionIndex = config["refraction_index"];
        if (_refractionIndex < 1)
            throw Error("refraction need to be > 1 when the object is glass");
    }
}
