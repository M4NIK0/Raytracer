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
    _currentRay = camera.getRay(x, y);
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

    RenderRay directLightRay = getSurfaceLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects, _lights, 20, 2);
    RenderRay reflexionsLightRay = getReflexionsLight(_currentRay, objects, 2);
    RenderRay diffuseLightRay = getDiffuseLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects, _lights, 20, 2);


    Color final_color = directLightRay.getColor() + reflexionsLightRay.getColor() + diffuseLightRay.getColor();

    return final_color;
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
    return raytracer::RenderRay();
}

raytracer::RenderRay
raytracer::Renderer::getSurfaceLight(const Point3D hit_point, const std::shared_ptr<IPrimitive> &object,
                                     const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                     const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces)
{
    RenderRay ray = getDirectLight(hit_point, object, objects, lights);
    return ray;
}

raytracer::RenderRay
raytracer::Renderer::getDiffuseLight(const raytracer::Point3D hit_point, const std::shared_ptr<IPrimitive> &object,
                                     const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                     const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces)
{
    return raytracer::RenderRay();
}

raytracer::RenderRay
raytracer::Renderer::getDirectLight(const raytracer::Point3D hit_point, const std::shared_ptr<IPrimitive> &object,
                                    const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                    const std::vector<std::shared_ptr<ILight>> &lights)
{
    // Get all direct light rays
    std::vector<RenderRay> directLightRays;

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));

    for (auto &light: lights)
    {
        // Get light ray
        RenderRay lightRay = light->getLightRay(hit_point);
        bool hit = false;
        for (auto &obj: objects)
        {
            // check if not self collide on surface turned towards light
            if (obj == object && object->getNormalFromPoint(hit_point).dot(lightRay.getRay().direction) > 0)
                continue;

            // Check if object between light and hit point
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

    // If no direct light, return black
    if (directLightRays.empty())
    {
        return ray;
    }

    // Mix all direct light rays
    for (auto lightRay : directLightRays)
    {
        ray.color = ray.color + lightRay.color * Color(object->getColor().r / 255.0, object->getColor().g / 255.0, object->getColor().b / 255.0) * lightRay.intensity * lightRay.intensity * object->getNormalFromPoint(hit_point).normalize().dot(lightRay.getRay().direction.normalize());
        ray.intensity = ray.intensity + lightRay.intensity;
    }

    // Clamp color
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
