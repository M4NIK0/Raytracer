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
    try {
        _normal = {config["normal"][0], config["normal"][1], config["normal"][2]};
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("normal not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("normal must be an array of 3 double"); }

    try {
        _position = {config["position"][0], config["position"][1], config["position"][2]};
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("position not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("position must be an array of 3 double");
    }

    try {
        libconfig::Setting& color = config["color"];
        _surfaceAbsorbtion.r = ((double)color[0]) / 255.0;
        _surfaceAbsorbtion.g = ((double)color[1]) / 255.0;
        _surfaceAbsorbtion.b = ((double)color[2]) / 255.0;
        if (_surfaceAbsorbtion.r < 0 || _surfaceAbsorbtion.r > 1 || _surfaceAbsorbtion.g < 0 || _surfaceAbsorbtion.g > 1 || _surfaceAbsorbtion.b < 0 || _surfaceAbsorbtion.b > 1)
            throw Error("color must be between 0 & 255");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("color not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("color must be an array of 3 double");
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
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("reflexion not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("reflexion must be a double");
    }
}
