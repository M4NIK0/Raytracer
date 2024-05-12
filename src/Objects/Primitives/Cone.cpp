/*
** EPITECH PROJECT, 2024
** Cone.cpp
** File description:
** raytracer
*/

#include "Cone.hpp"
#include <iostream>

raytracer::Cone::Cone() : _height(0), _baseRadius(0), _surfaceAbsorbtion({0, 0, 0}), _volumeAbsorbtion({0, 0, 0}), _emissionColor({0, 0, 0}) {}
raytracer::Cone::~Cone() = default;

raytracer::Point3D raytracer::Cone::hit(const Ray3D &ray)
{
    Vector3D v = Vector3D(0, 1, 0); // Assuming the cone is aligned with the y-axis
    Vector3D w = Vector3D(1, 0, 0); // Assuming w is perpendicular to v
    Vector3D ao = ray.origin - _apex;
    double k = _baseRadius / _height; // Assuming the base radius and height are known

    // Calculate coefficients for the quadratic equation
    double a = pow(ray.direction.dot(v), 2) - k * k * ray.direction.dot(w);
    double b = 2 * (ray.direction.dot(v) * ao.dot(v) - k * k * ray.direction.dot(w) * ao.dot(w));
    double c = pow(ao.dot(v), 2) - k * k * ao.dot(w);
    double discriminant = b * b - 4 * a * c;

    // If discriminant is negative, there are no real roots
    if (discriminant < 0) return {INFINITY, INFINITY, INFINITY};

    // Compute t0 and t1
    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);

    // If t1 is less than zero, the object is in the ray's negative direction
    if (t1 < 0) return {INFINITY, INFINITY, INFINITY};

    // If t0 is less than zero, the intersection point is at t1
    double t = t0 < 0 ? t1 : t0;

    return ray.origin + ray.direction * t;
}

raytracer::Vector3D raytracer::Cone::getSurfaceNormal(const Point3D &point)
{
    return (point - _position).normalize();
}

raytracer::Vector3D raytracer::Cone::getVolumeNormal(const Point3D &point)
{
    return (point - _position).normalize();
}

raytracer::Color raytracer::Cone::getSurfaceAbsorbtion(const Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::Cone::getSurfaceRoughness(const Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::Cone::getSurfaceTransparency(const Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::Cone::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::Cone::getVolumeAbsorbtionCoeff()
{
    return _volumeAbsorbtionCoeff;
}

raytracer::Color raytracer::Cone::getSurfaceEmission(const Point3D &point)
{
    return _emissionColor;
}

double raytracer::Cone::getSurfaceEmissionIntensity(const Point3D &point)
{
    return _emissionIntensity;
}

void raytracer::Cone::move(Vector3D vec)
{
    _position = _position + vec;
    _positionBackup = _position;
}

void raytracer::Cone::rotate(Vector3D vec)
{
}

bool raytracer::Cone::getGlassState(const Point3D &point)
{
    return _isGlass;
}

double raytracer::Cone::getRefractionIndex()
{
    return _refractionIndex;
}

double raytracer::Cone::getReflexionIndex(const Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::Cone::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::Cone::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::Cone::setGlassState(bool state)
{
    _isGlass = state;
}

void raytracer::Cone::setSurfaceEmission(raytracer::Color color)
{
    _emissionColor = color;
}

void raytracer::Cone::setSurfaceEmissionIntensity(double intensity)
{
    _emissionIntensity = intensity;
}

void raytracer::Cone::setMotion(Vector3D &translation, Vector3D &rotation)
{
    _translation = translation;
    _rotation = rotation;
}

void raytracer::Cone::initiateMotion(double time, size_t steps)
{
    Vector3D totalTranslation = _translation * time;
    Vector3D totalRotation = _rotation * time;

    _translationStep = totalTranslation / steps;
    _rotationStep = totalRotation / steps;

    _position = _position - totalTranslation / 2;
    _rotation = _rotation - totalRotation / 2;
}

void raytracer::Cone::resetMotion()
{
    _position = _positionBackup;
}

void raytracer::Cone::stepMotion()
{
    _position = _position + _translationStep;
    _rotation = _rotation + _rotationStep;
}

raytracer::Point3D raytracer::Cone::getCenter() const
{
    return _position;
}

void raytracer::Cone::parseData(libconfig::Setting &config)
{
    try {
        _height = config["height"];
        _baseRadius = config["base_radius"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("radius is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("radius must be a double");
    }

    try {
        libconfig::Setting& position = config["position"];
        _position.x = position[0];
        _position.y = position[1];
        _position.z = position[2];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("position is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("position must be a vector of double");
    }

    try {
        _reflexionIndex = config["reflexion"];
        if (_reflexionIndex < 0 || _reflexionIndex > 1)
            throw Error("reflexion must be between 0 and 1");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("reflexion is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("reflexion must be a double");
    }

    try {
        _surfaceRoughness = config["roughness"];
        if (_surfaceRoughness < 0 || _surfaceRoughness > 1)
            throw Error("roughness must be between 0 and 1");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("roughness is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("roughness must be a double");
    }
    try {
        libconfig::Setting& color = config["color"];
        _surfaceAbsorbtion.r = ((double)color[0]) / 255.0;
        _surfaceAbsorbtion.g = ((double)color[1]) / 255.0;
        _surfaceAbsorbtion.b = ((double)color[2]) / 255.0;
        if (_surfaceAbsorbtion.r < 0 || _surfaceAbsorbtion.r > 1 || _surfaceAbsorbtion.g < 0 || _surfaceAbsorbtion.g > 1 || _surfaceAbsorbtion.b < 0 || _surfaceAbsorbtion.b > 1)
            throw Error("color must be between 0 & 255");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("color is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("color must be a vector of double");
    }
    try {
        _isGlass = config["glass"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("glass is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("glass must be a boolean");
    }
    if (_isGlass) {
        try {
            _refractionIndex = config["refraction_index"];
            if (_refractionIndex < 1)
                throw Error("refraction_index need to be > 1 when the object is glass");
        } catch (libconfig::SettingNotFoundException &e) {
            throw Error("refraction_index is missing");
        } catch (libconfig::SettingTypeException &e) {
            throw Error("refraction_index must be a double");
        }
    }
}
