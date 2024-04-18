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

    RenderRay directLightRay = getSurfaceLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects,
                                               _lights, 5, 2);
    RenderRay reflexionsLightRay = getReflexionsLight(_currentRay, objects, 2);
    RenderRay diffuseLightRay = getDiffuseLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects,
                                                _lights, 5, 2);

    RenderRay finalRay = directLightRay + reflexionsLightRay + diffuseLightRay;

    return finalRay;
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
    return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    if (bounces <= 0)
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    std::vector<RenderRay> diffuseLightRays;
    Vector3D normal = object->getNormalFromPoint(hit_point);

    for (int i = 0; i < rays; ++i)
    {
        // Generate a random ray uniformly distributed over the hemisphere around the normal
        RenderRay randomRay = getRandomRay(hit_point, object);

        for (auto &obj: objects)
        {
            if (obj == object)
                continue;
            if (obj->hits(randomRay.getRay()))
            {
                _hitObjects.push_back(obj);
            }
        }

        if (_hitObjects.empty())
        {
            continue;
        }

        _sortHitObjectsByContactDistance();

        Point3D hitPoint = _hitObjects[0]->hitPosition(randomRay.getRay());

        RenderRay directLightRay = getDirectLight(hitPoint, _hitObjects[0], objects, lights);
        RenderRay reflexionsLightRay = getReflexionsLight(randomRay.getRay(), objects, bounces - 1);
        RenderRay diffuseLightRay = getDiffuseLight(hitPoint, _hitObjects[0], objects, lights, rays, bounces - 1);

        // Use a different method to attenuate the light intensity based on distance
        double distance = Point3D::distance(hit_point, hitPoint);
        double attenuation = 1 / (1 + 0.1 * distance);  // Linear attenuation

        directLightRay.color = directLightRay.color * attenuation;
        reflexionsLightRay.color = reflexionsLightRay.color * attenuation;
        diffuseLightRay.color = diffuseLightRay.color * attenuation;

        RenderRay finalRay = directLightRay + reflexionsLightRay + diffuseLightRay;

        diffuseLightRays.push_back(finalRay);
    }

    if (diffuseLightRays.empty())
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));

    for (auto &diffuseLightRay: diffuseLightRays)
    {
        ray.color = ray.color + diffuseLightRay.color;
        ray.intensity = ray.intensity + diffuseLightRay.intensity;
    }

    return ray;
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
    for (auto lightRay: directLightRays)
    {
        ray.color = ray.color + lightRay.color * Color(object->getColor().r / 255.0, object->getColor().g / 255.0,
                                                       object->getColor().b / 255.0) * lightRay.intensity *
                                lightRay.intensity * object->getNormalFromPoint(hit_point).normalize().dot(
                lightRay.getRay().direction.normalize());
        ray.intensity = ray.intensity + lightRay.intensity;
    }

    return ray;
}

raytracer::RenderRay
raytracer::Renderer::getRandomRay(const raytracer::Point3D &origin, const std::shared_ptr<IPrimitive> &object)
{
    if (!object) {
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
    color = color * (1 / max_intensity);
    color.cap(); // Ensure the color values are within the range 0-255
    return color;
}
