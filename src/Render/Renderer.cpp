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

    RenderRay directLightRay = getSurfaceLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects, _lights, 100, 2);
    return directLightRay.color;
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

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));

    if (bounces > 0)
    {
        RenderRay diffuseLightRay(Point3D(0, 0, 0), Vector3D(0, 0, 0));
        for (int i = 0; i < rays; ++i)
        {
            RenderRay randomRay = getRandomRay(hit_point, object);
            for (auto &obj: objects)
            {
                if (obj == object)
                    continue;
                if (obj->hits(randomRay.getRay()))
                {
                    RenderRay hitRay = getSurfaceLight(obj->hitPosition(randomRay.getRay()), obj, objects, lights, rays, bounces - 1);
                    diffuseLightRay.color = hitRay.color + diffuseLightRay.color * (1 / Point3D::distance(hit_point, obj->hitPosition(randomRay.getRay())));
                    diffuseLightRay.intensity += hitRay.intensity;
                    break;
                }
            }
        }
        diffuseLightRay.color = Color(diffuseLightRay.color.r / rays, diffuseLightRay.color.g / rays, diffuseLightRay.color.b / rays);
        diffuseLightRay.intensity /= rays;

        ray.color = ray.color + diffuseLightRay.color * object->getColor() * 0.1;
        ray.intensity += diffuseLightRay.intensity;
    }

    for (auto &light: lights)
    {
        RenderRay lightRay = light->getLightRay(hit_point);
        bool hit = false;
        for (auto &obj: objects)
        {
            // check if not self collide on surface turned towards light
            if (obj == object && object->getNormalFromPoint(hit_point).dot(lightRay.getRay().direction) > 0)
                continue;
            if (obj->hits(lightRay.getRay()))
            {
                hit = true;
                break;
            }
        }
        // Light if no object between light and hit point
        if (!hit)
        {
            lightRay.color = light->getColor();
            lightRay.intensity = light->getIntensityFromDistance(Point3D::distance(hit_point, light->getPosition()));
            directLightRays.push_back(lightRay);
        }
    }

    if (directLightRays.empty())
    {
        return ray;
    }

    for (auto lightRay : directLightRays)
    {
        ray.color = ray.color + lightRay.color * Color(object->getColor().r / 255.0, object->getColor().g / 255.0, object->getColor().b / 255.0) * lightRay.intensity * lightRay.intensity * object->getNormalFromPoint(hit_point).normalize().dot(lightRay.getRay().direction.normalize());
        ray.intensity = ray.intensity + lightRay.intensity;
    }

    ray.color.cap();
    return ray;
}

raytracer::RenderRay
raytracer::Renderer::getRandomRay(const raytracer::Point3D &origin, const std::shared_ptr<IPrimitive> &object)
{
    double x = (double)rand() / RAND_MAX;
    double y = (double)rand() / RAND_MAX;
    double z = (double)rand() / RAND_MAX;

    Vector3D randomDirection = Vector3D(x, y, z).normalize();

    if (object->getNormalFromPoint(origin).dot(randomDirection) < 0)
    {
        randomDirection = randomDirection * -1;
    }

    return RenderRay(Ray3D(origin, randomDirection));
}
