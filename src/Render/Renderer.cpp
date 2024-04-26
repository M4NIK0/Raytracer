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
    Color color = object->getColor();
    color.normalize();
    object->setColor(color);

    objects.push_back(object);
}

raytracer::RenderRay raytracer::Renderer::traceRay(int x, int y)
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
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    _sortHitObjectsByContactDistance();

    RenderRay directLightRay = getDirectLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects, _lights);
    RenderRay reflexionsLightRay = getReflexionsLight(_currentRay, objects, _hitObjects[0], 2);
    RenderRay diffuseLightRay = getDiffuseLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects, _lights, 10, 2);
    RenderRay refractionsLightRay = getRefractionsLight(_hitObjects[0]->hitPosition(_currentRay), _currentRay, objects, 2, _hitObjects[0]);

    RenderRay finalRay = directLightRay + reflexionsLightRay + diffuseLightRay + refractionsLightRay;
    return finalRay;
}

void raytracer::Renderer::renderImage()
{
}

void raytracer::Renderer::_sortHitObjectsByContactDistance()
{
    double nearestDistance = INFINITY;
    std::shared_ptr<IPrimitive> nearestObject;

    for (auto obj : _hitObjects)
    {
        double currentDistance = Point3D::distance(_currentRay.origin, obj->hitPosition(_currentRay));

        if (currentDistance < nearestDistance)
        {
            nearestDistance = currentDistance;
            nearestObject = obj;
        }
    }

    _hitObjects.clear();

    _hitObjects.push_back(nearestObject);
}

void raytracer::Renderer::addLight(std::shared_ptr<ILight> light)
{
    _lights.push_back(light);
}

raytracer::RenderRay
raytracer::Renderer::getReflexionsLight(const Ray3D &ray, const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                        std::shared_ptr<IPrimitive> object, int bounces)
{
    if (object->getReflexionIndice(ray) == 0.0)
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    if (bounces <= 0)
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    if (!object)
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    Point3D hitPoint = object->hitPosition(ray);
    Vector3D normal = object->getNormalFromPoint(hitPoint);
    normal.normalize();

    Ray3D reflectedRay = object->hitReflectedRay(ray);

    _hitObjects.clear();

    for (auto &obj: objects)
    {
        if (obj == object)
            continue;
        if (obj->hits(reflectedRay))
        {
            _hitObjects.push_back(obj);
        }
    }

    if (_hitObjects.empty())
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    _sortHitObjectsByContactDistance();

    RenderRay directLightRay = getDirectLight(_hitObjects[0]->hitPosition(reflectedRay), _hitObjects[0], objects, _lights);
    RenderRay reflexionsLightRay = getReflexionsLight(reflectedRay, objects, _hitObjects[0], (bounces - 1));
    RenderRay diffuseLightRay = getDiffuseLight(_hitObjects[0]->hitPosition(reflectedRay), _hitObjects[0], objects,_lights, 100, (bounces - 1));
    RenderRay refractionsLightRay = getRefractionsLight(_hitObjects[0]->hitPosition(reflectedRay), reflectedRay, objects, (bounces - 1), _hitObjects[0]);

    RenderRay finalRay = directLightRay + reflexionsLightRay + diffuseLightRay + refractionsLightRay;

    finalRay.color = finalRay.color * object->getReflexionIndice(ray);

    return finalRay;
}

raytracer::RenderRay
raytracer::Renderer::getSurfaceLight(const Point3D hit_point, const std::shared_ptr<IPrimitive> object,
                                     const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                     const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces)
{
    RenderRay ray = getDirectLight(hit_point, object, objects, lights);
    return ray;
}

raytracer::RenderRay
raytracer::Renderer::getDiffuseLight(const Point3D hit_point, const std::shared_ptr<IPrimitive> object,
                                     const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                     const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces)
{
    std::vector <RenderRay> diffuseLightRays;

    if (bounces <= 0)
    {
        return RenderRay();
    }

    for (int i = 0; i < rays; ++i)
    {
        RenderRay currentRay = getRandomRay(hit_point, object);

        _hitObjects.clear();
        for (auto &obj : objects)
        {
            if (obj == object && object->getNormalFromPoint(hit_point).dot(currentRay.direction) > 0)
                continue;

            if (obj->hits(currentRay))
                _hitObjects.push_back(obj);
        }

        if (_hitObjects.empty())
            continue;

        _sortHitObjectsByContactDistance();

        Point3D contactPoint = _hitObjects[0]->hitPosition(currentRay);
        double distance = Point3D::distance(currentRay.origin, contactPoint);

        RenderRay directLight = getDirectLight(contactPoint, _hitObjects[0], objects, lights);
        RenderRay diffuseLight = getDiffuseLight(contactPoint, _hitObjects[0], objects, lights, rays, (bounces - 1));

        currentRay.color = (directLight.color + diffuseLight.color) * object->getColor();

        diffuseLightRays.push_back(currentRay);
    }

    RenderRay finalRay = RenderRay();
    for (auto ray : diffuseLightRays)
    {
        finalRay.color = finalRay.color + ray.color;
    }

    finalRay.color = finalRay.color * (1.0 / rays);

    return finalRay;
}

raytracer::RenderRay
raytracer::Renderer::getDirectLight(const Point3D hit_point, const std::shared_ptr<IPrimitive> object,
                                    const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                    const std::vector<std::shared_ptr<ILight>> &lights)
{
    // Get all direct light rays
    std::vector<RenderRay> directLightRays;

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));

    for (auto &light: lights)
    {
        // Get light rays
        std::vector<Ray3D> lightRays = light->getLightRays(hit_point);

        for (auto &lightRay: lightRays)
        {
            bool hit = false;
            for (auto &obj: objects)
            {
                // check if not self collide on surface turned towards light
                if (obj == object && object->getNormalFromPoint(hit_point).dot(lightRay.direction) > 0)
                    continue;

                // Check if object between light and hit point
                if (obj->hits(lightRay))
                {
                    hit = true;
                    break;
                }
            }
            // Light if no object between light and hit point
            if (!hit)
            {
                RenderRay directLightRay = RenderRay(lightRay);
                Vector3D normal = object->getNormalFromPoint(hit_point);
                directLightRay.color = light->getColor() * light->getIntensityFromDistance(Point3D::distance(hit_point, light->getPosition())) * normal.dot(lightRay.direction);
                directLightRays.push_back(directLightRay);
            }
        }
    }

    // If no direct light, return black
    if (directLightRays.empty())
    {
        return ray;
    }

    // Mix all direct light rays
    for (auto lightRay: directLightRays)
    {
        ray.color = ray.color + lightRay.color;
    }

    ray.color = ray.color * object->getColor() * (1 - object->getReflexionIndice(ray));
    return ray;
}

raytracer::RenderRay
raytracer::Renderer::getRandomRay(const raytracer::Point3D &origin, const std::shared_ptr<IPrimitive> object)
{
    if (!object)
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    double x = (double) rand() / RAND_MAX;
    double y = (double) rand() / RAND_MAX;
    double z = (double) rand() / RAND_MAX;

    Vector3D randomDirection = Vector3D(x, y, z);
    randomDirection = randomDirection.normalize();

    Vector3D normal = object->getNormalFromPoint(origin);
    double normalCompute = normal.dot(randomDirection);

    if (normalCompute < 0)
    {
        randomDirection = randomDirection * -1;
    }

    return RenderRay(Ray3D(origin, randomDirection));
}

raytracer::Color raytracer::Renderer::getColorFromLight(const raytracer::RenderRay &ray, double max_intensity)
{
    raytracer::Color color = ray.color;
    color = color * (1.0 / max_intensity) * 255.0;
    return color;
}

raytracer::RenderRay raytracer::Renderer::getRefractionsLight(Point3D hitPoint, const Ray3D &ray,
                                                   const std::vector<std::shared_ptr<IPrimitive>> &objects, int bounces,
                                                   std::shared_ptr<IPrimitive> object)
{
    Vector3D normal = object->getNormalFromPoint(hitPoint);
    normal.normalize();

    if (!object->isGlass())
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    double refractionIndex = object->getRefractionxionIndice(ray);

    double cosTheta1 = -normal.dot(ray.direction);
    double eta = 1 / refractionIndex;  // Assuming the incident ray is in air or vacuum
    double k = 1 - eta * eta * (1 - cosTheta1 * cosTheta1);

    RenderRay refracted;

    if (k < 0)
    {
        // Total internal reflection, return zero vector
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }
    else
    {
        refracted = RenderRay(Ray3D(hitPoint, (ray.direction * eta) + (normal * (eta * cosTheta1 - sqrt(k)))));
    }

    // exit point
    refracted.origin = refracted.origin + refracted.direction * 0.1;
    Point3D exitPoint = object->hitPosition(refracted.getRay());

    Vector3D normalExit = (object->getNormalFromPoint(exitPoint) * (-1));

    double cosTheta2 = -normalExit.dot(refracted.direction);
    double eta2 = refractionIndex;
    double k2 = 1 - eta2 * eta2 * (1 - cosTheta2 * cosTheta2);

    refracted = RenderRay(Ray3D(exitPoint, (refracted.direction * eta2) + (normalExit * (eta2 * cosTheta2 - sqrt(k2)))));

    _hitObjects.clear();

    for (auto &obj: objects)
    {
        if (obj == object)
            continue;
        if (obj->hits(refracted.getRay()))
        {
            _hitObjects.push_back(obj);
        }
    }

    if (_hitObjects.empty())
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    _sortHitObjectsByContactDistance();

    Point3D outsideHitPoint = _hitObjects[0]->hitPosition(refracted.getRay());

    RenderRay directLightRay = getDirectLight(outsideHitPoint, _hitObjects[0], objects, _lights);
    RenderRay reflexionsLightRay = getReflexionsLight(refracted.getRay(), objects, _hitObjects[0], bounces);
    RenderRay diffuseLightRay = getDiffuseLight(outsideHitPoint, _hitObjects[0], objects, _lights, 100, bounces);
    RenderRay refractionsLightRay = getRefractionsLight(outsideHitPoint, refracted.getRay(), objects, bounces, _hitObjects[0]);

    RenderRay finalRay = directLightRay + reflexionsLightRay + diffuseLightRay + refractionsLightRay;

    return finalRay;
}
