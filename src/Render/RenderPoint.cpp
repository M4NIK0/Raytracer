/*
** EPITECH PROJECT, 2024
** RenderPoint.cpp
** File description:
** raytracer
*/

#include "RenderPoint.hpp"

raytracer::RenderPoint::RenderPoint() = default;

raytracer::RenderPoint::~RenderPoint() = default;

bool raytracer::RenderPoint::hitObject(std::shared_ptr<IObject> object, raytracer::Ray3D &ray)
{
    Point3D hitPoint = object->hit(ray);

    if (hitPoint == Point3D(INFINITY, INFINITY, INFINITY))
        return false;

    this->object = object;
    this->hitPoint = hitPoint;
    this->ray = ray;
    this->surfaceNormal = object->getSurfaceNormal(hitPoint);
    this->volumeNormal = object->getVolumeNormal(hitPoint);
    this->distance = hitPoint.distance(ray.origin, hitPoint);

    return true;
}
