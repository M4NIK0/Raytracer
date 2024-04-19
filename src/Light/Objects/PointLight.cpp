/*
** EPITECH PROJECT, 2024
** PointLight.cpp
** File description:
** raytracer
*/

#include "PointLight.hpp"

raytracer::PointLight::~PointLight() = default;

raytracer::Ray3D raytracer::PointLight::getLightRay(const raytracer::Point3D &hitPoint)
{
    raytracer::Vector3D direction = _position - hitPoint;
    return raytracer::Ray3D(hitPoint, direction.normalize());
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
