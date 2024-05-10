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

}
