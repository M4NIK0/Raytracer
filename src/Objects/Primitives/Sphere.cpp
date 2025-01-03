/*
** EPITECH PROJECT, 2024
** Sphere.cpp
** File description:
** raytracer
*/

#include "Sphere.hpp"
#include <iostream>

raytracer::Sphere::Sphere() : _radius(1), _position(Point3D(0, 0, 0)), _surfaceRoughness(0), _surfaceAbsorbtion(Color(0, 0, 0)),
                              _volumeAbsorbtion(Color(0, 0, 0)), _volumeAbsorbtionCoeff(0), _emissionColor(Color(0, 0, 0)),
                              _emissionIntensity(0), _isGlass(false), _reflexionIndex(0), _refractionIndex(1) {}

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

}

void raytracer::Sphere::stepMotion()
{
    _position = _position + _translationStep;
    _rotation = _rotation + _rotationStep;
}

raytracer::Point3D raytracer::Sphere::getCenter() const
{
    return _position;
}
   
void raytracer::Sphere::parseData(libconfig::Setting &config)
{
    try {
        _radius = config["radius"];
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
        libconfig::Setting& translation = config["translationSpeed"];
        _translation = Vector3D(translation[0], translation[1], translation[2]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("translationSpeed is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("translationSpeed must be a vector of double");
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
        _emissionIntensity = config["emissionIntensity"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("emissionIntensity not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("emissionIntensity must be a double");
    }

    try {
        _emissionColor = {config["emissionColor"][0], config["emissionColor"][1], config["emissionColor"][2]};
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("emissionColor not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("emissionColor must be an array of 3 double");
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
        _isGlass = config["glass"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("glass is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("glass must be a boolean");
    }
    if (_isGlass) {
        try {
            _refractionIndex = config["refractionIndex"];
            if (_refractionIndex < 1)
                throw Error("refractionIndex need to be > 1 when the object is glass");
        } catch (libconfig::SettingNotFoundException &e) {
            throw Error("refractionIndex is missing");
        } catch (libconfig::SettingTypeException &e) {
            throw Error("refractionIndex must be a double");
        }
    }
}
