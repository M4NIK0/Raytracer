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

    RenderRay directLightRay = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    if (!_hitObjects[0]->isGlass())
    {
        directLightRay = getDirectLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects, _lights);
    }
    RenderRay reflexionsLightRay = getReflexionsLight(_currentRay, objects, 2);
    RenderRay diffuseLightRay = getDiffuseLight(_hitObjects[0]->hitPosition(_currentRay), _hitObjects[0], objects,
                                                _lights, 100, 2);
    RenderRay refractionsLightRay = getRefractionsLight(_hitObjects[0]->hitPosition(_currentRay), _currentRay, objects, 2, _hitObjects[0]);

//    std::cout << "Direct light: " << directLightRay.intensity << std::endl;
    std::cout << "Reflexions light: " << reflexionsLightRay.intensity << std::endl;
    std::cout << "Diffuse light: " << diffuseLightRay.intensity << std::endl << std::endl;
    std::cout << "Refractions light: " << refractionsLightRay.intensity << std::endl << std::endl;
    RenderRay finalRay = directLightRay + reflexionsLightRay + diffuseLightRay + refractionsLightRay;

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
    std::vector<RenderRay> diffuseLightRays;
    for (int i = 0; i < rays; i++)
    {
        RenderRay ray = getRandomRay(hit_point, object);
        _hitObjects.clear();
        for (auto &obj: objects)
        {
            if (obj == object)
                continue;
            if (obj->hits(ray.getRay()))
            {
                _hitObjects.push_back(obj);
                break;
            }
        }

        if (_hitObjects.empty())
        {
            continue;
        }

        _sortHitObjectsByContactDistance();

        std::shared_ptr<IPrimitive> hit_Object = _hitObjects[0];
        diffuseLightRays.push_back(getDirectLight(hit_point, hit_Object, objects, lights));
    }

    if (diffuseLightRays.empty())
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    double totalIntensity = 0.0;

    for (auto &diffuseLightRay: diffuseLightRays)
    {
        totalIntensity += diffuseLightRay.intensity;
    }

    Color totalColor(0, 0, 0);

    for (auto &diffuseLightRay: diffuseLightRays)
    {
        totalColor = totalColor + diffuseLightRay.color * object->getColor() * diffuseLightRay.intensity *
                                    object->getNormalFromPoint(hit_point).normalize().dot(diffuseLightRay.getRay().direction.normalize());
    }

    ray.color = totalColor;

    ray.intensity = totalIntensity / static_cast<double>(rays);  // Average the intensity over all rays

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
        ray.color = ray.color + lightRay.color * object->getColor() * lightRay.intensity *
                                lightRay.intensity * object->getNormalFromPoint(hit_point).normalize().dot(
                lightRay.getRay().direction.normalize());
        ray.intensity = ray.intensity + lightRay.intensity;
    }

    return ray;
}

raytracer::RenderRay
raytracer::Renderer::getRandomRay(const raytracer::Point3D &origin, const std::shared_ptr<IPrimitive> &object)
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
    color = color * (1 / max_intensity);
    color.cap(); // Ensure the color values are within the range 0-255
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
    return directLightRay;
}
