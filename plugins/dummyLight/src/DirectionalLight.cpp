/*
** EPITECH PROJECT, 2024
** DirectionalLight.cpp
** File description:
** dummyLight
*/

#include "DirectionalLight.hpp"

raytracer::DirectionalLight::~DirectionalLight() = default;

void raytracer::DirectionalLight::parseData(libconfig::Setting &config)
{
    try {
        _direction = raytracer::Vector3D(config["direction"]["x"], config["direction"]["y"], config["direction"]["z"]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("direction not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("direction need to be an array of double");
    }

    try {
        libconfig::Setting &color = config["color"];
        _color = raytracer::Color(color[0], color[1], color[2]);
        _color.normalize();

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


std::vector<raytracer::Ray3D> raytracer::DirectionalLight::getLightRays(const raytracer::Point3D &hitPoint)
{
    Ray3D ray;

    ray.origin = hitPoint;
    ray.direction = Vector3D()-_direction;

    ray.direction.normalize();

    return {ray};
}
