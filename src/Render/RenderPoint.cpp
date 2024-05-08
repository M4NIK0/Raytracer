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

void raytracer::RenderPoint::hitNearestObject(const std::vector<std::shared_ptr<IObject>> &objects, raytracer::Ray3D &ray)
{
    double minimalDistance = INFINITY;
    RenderPoint nearestPoint;

    for (auto &object: objects)
    {
        RenderPoint point;
        if (point.hitObject(object, ray) && point.distance < minimalDistance)
        {
            nearestPoint = point;
            minimalDistance = point.distance;
        }
    }

    this->distance = minimalDistance;
    this->hitPoint = nearestPoint.hitPoint;
    this->object = nearestPoint.object;
    this->ray = nearestPoint.ray;
    this->surfaceNormal = nearestPoint.surfaceNormal;
    this->volumeNormal = nearestPoint.volumeNormal;
}

bool raytracer::RenderPoint::hits(const std::shared_ptr<IObject> &object, const raytracer::Ray3D &ray) const
{
    Point3D hitPoint = object->hit(ray);

    if (hitPoint == Point3D(INFINITY, INFINITY, INFINITY))
        return false;

    return true;
}

bool raytracer::RenderPoint::hitsSomething(const std::vector<std::shared_ptr<IObject>> &objects, const raytracer::Ray3D &ray) const
{
    RenderPoint point;

    point.hitNearestObject(const_cast<std::vector<std::shared_ptr<IObject>> &>(objects), const_cast<raytracer::Ray3D &>(ray));

    if (point.object && point.object != object)
        return true;

    return false;
}
