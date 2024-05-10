/*
** EPITECH PROJECT, 2024
** PointLight.cpp
** File description:
** raytracer
*/

#include "PointLight.hpp"

raytracer::PointLight::~PointLight() = default;

std::vector<raytracer::Ray3D> raytracer::PointLight::getLightRays(const Point3D &hitPoint)
{
    raytracer::Vector3D direction = _position - hitPoint;
    return {raytracer::Ray3D(hitPoint, direction.normalize())};
}

raytracer::Color raytracer::PointLight::getColor()
{
    return _color;
}

double raytracer::PointLight::getIntensity()
{
    return _intensity;
}

double raytracer::PointLight::getIntensityFromDistance(double distance)
{
    return _intensity / (distance * distance);
}

void raytracer::PointLight::parseData(libconfig::Setting &config)
{
    try {
        libconfig::Setting &position = config["position"];
        _position = raytracer::Point3D(position["x"], position["y"], position["z"]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("position not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("position need to be an array of double");
    }

    try {
        libconfig::Setting &color = config["color"];
        _color = raytracer::Color(color[0], color[1], color[2]);

    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("color not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("color need to be an array of double");
    }
    try {
        _intensity = config["intensity"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("intensity not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("intensity need to be a double");
    }
}
