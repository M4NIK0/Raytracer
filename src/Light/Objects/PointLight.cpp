/*
** EPITECH PROJECT, 2024
** PointLight.cpp
** File description:
** raytracer
*/

#include "PointLight.hpp"

raytracer::PointLight::PointLight() : _color(raytracer::Color(255, 255, 255)),
                                      _intensity(1),
                                      _position(raytracer::Point3D(0, 0, 0)) {}

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
        _color.r = config["color"]["r"];
        _color.g = config["color"]["g"];
        _color.b = config["color"]["b"];
        if (_color.r < 0 || _color.r > 255 || _color.g < 0 || _color.g > 255 || _color.b < 0 || _color.b > 255)
            throw Error("color must be between 0 and 255");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("color not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("color must be an integer between 0 and 255");
    }

    try {
        _intensity = config["intensity"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("intensity not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("intensity must be a double");
    }

    try {
        _position.x = config["position"]["x"];
        _position.y = config["position"]["y"];
        _position.z = config["position"]["z"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("position not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("position must be an object with three double. x, y and z");
    }
}
