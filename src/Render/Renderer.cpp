/*
** EPITECH PROJECT, 2024
** Renderer.cpp
** File description:
** raytracer
*/

#include "Renderer.hpp"
#include "RenderRay.hpp"

raytracer::Renderer::~Renderer() = default;

void raytracer::Renderer::addObject(std::shared_ptr<IPrimitive> object)
{
    objects.push_back(object);
}

raytracer::Color raytracer::Renderer::traceRay(int x, int y)
{
    _currentRay = _camera.getRay(x, y);
    _hitObjects.clear();

    for (auto &object: objects)
    {
        if (object->hits(_currentRay))
        {
            _hitObjects.push_back(object);
        }
    }

    if (_hitObjects.empty())
    {
        return Color(0, 0, 0);
    }

    _sortHitObjectsByContactDistance();

    RenderRay finalRay = getSurfaceLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects, _lights, 1, 1);
    return finalRay.color;
}

void raytracer::Renderer::renderImage()
{
}

void raytracer::Renderer::_sortHitObjectsByContactDistance()
{
    std::map<double, std::shared_ptr<IPrimitive>> distanceToObject;

    for (auto &object: _hitObjects)
    {
        distanceToObject[Point3D::distance(_currentRay.origin, object->hitPosition(_currentRay))] = object;
    }

    _hitObjects.clear();

    for (auto &object: distanceToObject)
    {
        _hitObjects.push_back(object.second);
    }
}

void raytracer::Renderer::addLight(std::shared_ptr<ILight> light)
{
    _lights.push_back(light);
}

raytracer::RenderRay raytracer::Renderer::getReflexionsLight(const raytracer::Ray3D &ray,
                                                             const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                                             int bounces)
{
    return RenderRay(ray);
}

raytracer::RenderRay
raytracer::Renderer::getSurfaceLight(const Point3D hit_point, const std::shared_ptr<IPrimitive> &object,
                                     const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                     const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces)
{
    std::vector<RenderRay> directLightRays;
    std::vector<RenderRay> reflexionLightRays;

    for (auto &light: lights)
    {
        RenderRay lightRay = light->getLightRay(hit_point);
        bool hit = false;
        for (auto &obj: objects)
        {
            // check if not self collide on surface turned to light
            if (obj == object && object->getNormalFromPoint(hit_point).dot(lightRay.getRay().direction) > 0)
                continue;
            if (obj->hits(lightRay.getRay()))
            {
                hit = true;
                break;
            }
        }
        if (!hit)
        {
            lightRay.color = light->getColor();
            lightRay.intensity = light->getIntensityFromDistance(Point3D::distance(hit_point, light->getPosition()));
            directLightRays.push_back(lightRay);
        }
    }

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));

    if (directLightRays.empty())
    {
        return ray;
    }

    for (auto lightRay : directLightRays)
    {
        ray.color = ray.color + lightRay.color * Color(object->getColor().r / 255.0, object->getColor().g / 255.0, object->getColor().b / 255.0) * lightRay.intensity;
    }

    // cap color between 0 and 255
    ray.color.cap();
    return ray;
}
