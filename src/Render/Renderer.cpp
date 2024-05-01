/*
** EPITECH PROJECT, 2024
** Renderer.cpp
** File description:
** raytracer
*/

#include "Renderer.hpp"
#include "RenderRay.hpp"
#include "RenderPoint.hpp"

raytracer::Renderer::~Renderer() = default;

void raytracer::Renderer::addObject(std::shared_ptr<IObject> object)
{
    _renderData.objects.push_back(object);
}

void raytracer::Renderer::addLight(std::shared_ptr<ILight> light)
{
    _renderData.lights.push_back(light);
}

raytracer::RenderRay raytracer::Renderer::traceRay(int x, int y)
{
    Ray3D ray = camera.getRay(x, y);
    RenderPoint point;

    point.hitNearestObject(_renderData.objects, ray);

    if (!point.object)
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    RenderRay directLight = getDirectLight(point, _renderData);
    RenderRay reflexionsLight = getReflexionsLight(point, _renderData, _renderData.maxBounces);
    RenderRay diffuseLight = getDiffuseLight(point, _renderData, _renderData.maxBounces);
//    RenderRay refractionsLight = getRefractionsLight(point, _renderData, _renderData.maxBounces);

    RenderRay finalRay = directLight + reflexionsLight + diffuseLight;// + refractionsLight;

    return finalRay;
}

raytracer::Vector3D raytracer::Renderer::getRandomRayFromCone(const raytracer::Vector3D &normal, double angle)
{
    // Generate two random numbers
    double u = static_cast<double>(rand()) / RAND_MAX;
    double v = static_cast<double>(rand()) / RAND_MAX;

    // Convert the random numbers to spherical coordinates within the cone
    double theta = 2 * M_PI * u;
    double phi = acos(1 - v * (1 - cos(angle)));

    // Convert the spherical coordinates to Cartesian coordinates
    double x = sin(phi) * cos(theta);
    double y = sin(phi) * sin(theta);
    double z = cos(phi);

    // Create the random vector
    raytracer::Vector3D randomVector(x, y, z);

    return randomVector;
}

raytracer::RenderRay
raytracer::Renderer::getDirectLight(const RenderPoint &point, const renderData &data)
{
    // Get all direct light rays
    std::vector<RenderRay> directLightRays;

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));

    for (auto &light: _renderData.lights)
    {
        // Get light rays
        std::vector<Ray3D> lightRays = light->getLightRays(point.hitPoint);

        for (auto &lightRay: lightRays)
        {
            lightRay.origin = lightRay.origin + lightRay.direction * -0.01;

            // Create a shadow ray towards the light source
            Ray3D shadowRay(point.hitPoint + point.surfaceNormal * 0.001, lightRay.direction);
            RenderPoint shadowHitPoint;

            // If the shadow ray hits something before reaching the light source, continue to the next light source
            if (shadowHitPoint.hitsSomething(data.objects, shadowRay))
            {
                continue;
            }

            RenderRay directLightRay = RenderRay(lightRay);
            directLightRay.color = light->getColor() * light->getIntensityFromDistance(Point3D::distance(point.hitPoint, light->getPosition())) * point.surfaceNormal.dot(lightRay.direction);
            directLightRays.push_back(directLightRay);
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

    ray.color = ray.color * point.object->getSurfaceAbsorbtion(point.hitPoint) * (1 - point.object->getReflexionIndex(point.hitPoint));
    return ray;
}

raytracer::RenderRay
raytracer::Renderer::getReflexionsLight(const RenderPoint &point, const renderData &data, int bounces)
{
    if (bounces <= 0)
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    // Create the reflection ray
    Vector3D reflection = point.ray.direction - point.surfaceNormal * 2 * point.ray.direction.dot(point.surfaceNormal);
    Ray3D reflectionRay(point.hitPoint + point.surfaceNormal * 0.001, reflection);

    // Create the reflection point
    RenderPoint reflectionPoint;
    reflectionPoint.hitNearestObject(data.objects, reflectionRay);

    // If the reflection ray hits nothing, return black
    if (!reflectionPoint.object)
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    // Get the direct light
    RenderRay directLight = getDirectLight(reflectionPoint, data);

    // Get the reflection light
    RenderRay reflectionLight = getReflexionsLight(reflectionPoint, data, bounces - 1);

    // Mix the direct and reflection light
    RenderRay ray = directLight + reflectionLight;
    ray.color = ray.color * point.object->getReflexionIndex(point.hitPoint);

    return ray;
}

raytracer::RenderRay raytracer::Renderer::getDiffuseLight(const RenderPoint &point, const renderData &data, int bounces)
{
    if (bounces <= 0)
    {
        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    }

    Color totalColor(0, 0, 0);
    for (int i = 0; i < data.diffuseRays; ++i)
    {
        // Get the random ray
        Vector3D randomRay = getRandomRayFromCone(point.surfaceNormal, M_PI / 2);
        Ray3D randomRayDirection(point.hitPoint + point.surfaceNormal * 0.001, randomRay);

        // Create the random point
        RenderPoint randomPoint;
        randomPoint.hitNearestObject(data.objects, randomRayDirection);

        // If the random ray hits nothing, continue to the next ray
        if (!randomPoint.object)
        {
            continue;
        }

        // Get the direct light
        RenderRay directLight = getDirectLight(randomPoint, data);

        // Get the diffuse light
        RenderRay diffuseLight = getDiffuseLight(randomPoint, data, bounces - 1);

        // Get the reflection light
        RenderRay reflectionLight = getReflexionsLight(randomPoint, data, bounces - 1);

        // Mix the direct and diffuse light
        RenderRay ray = directLight + diffuseLight + reflectionLight;
        ray.color = ray.color * point.object->getSurfaceAbsorbtion(point.hitPoint);

        // Add the color of this ray to the total color
        totalColor = totalColor + ray.color;
    }

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    // Calculate the mean color
    ray.color = totalColor * (1.0 / data.diffuseRays);

    // Return a ray with the mean color
    return ray;
}

//raytracer::RenderRay raytracer::Renderer::getRefractionsLight(Point3D hitPoint, const Ray3D &ray,
//                                                              const std::vector<std::shared_ptr<IObject>> &objects, int bounces,
//                                                              std::shared_ptr<IObject> object)
//{
//    Vector3D normal = object->getNormalFromPoint(hitPoint);
//    normal.normalize();
//
//    if (!object->getGlassState())
//    {
//        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
//    }
//
//    double refractionIndex = object->getRefractionxionIndex();
//
//    double cosTheta1 = -normal.dot(ray.direction);
//    double eta = 1 / refractionIndex;  // Assuming the incident ray is in air or vacuum
//    double k = 1 - eta * eta * (1 - cosTheta1 * cosTheta1);
//
//    RenderRay refracted;
//
//    if (k < 0)
//    {
//        Total internal reflection, return zero vector
//        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
//    }
//    else
//    {
//        refracted = RenderRay(Ray3D(hitPoint, (ray.direction * eta) + (normal * (eta * cosTheta1 - sqrt(k)))));
//    }
//
//    exit point
//    refracted.origin = refracted.origin + refracted.direction * 0.1;
//    Point3D exitPoint = object->hit(refracted.getRay());
//
//    Vector3D normalExit = (object->getNormalFromPoint(exitPoint) * (-1));
//
//    double cosTheta2 = -normalExit.dot(refracted.direction);
//    double eta2 = refractionIndex;
//    double k2 = 1 - eta2 * eta2 * (1 - cosTheta2 * cosTheta2);
//
//    refracted = RenderRay(Ray3D(exitPoint, (refracted.direction * eta2) + (normalExit * (eta2 * cosTheta2 - sqrt(k2)))));
//
//    _hitObjects.clear();
//
//    for (auto &obj: objects)
//    {
//        if (obj == object)
//            continue;
//        if (obj->hits(refracted.getRay()))
//        {
//            _hitObjects.push_back(obj);
//        }
//    }
//
//    if (_hitObjects.empty())
//    {
//        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
//    }
//
//    _sortHitObjectsByContactDistance();
//
//    Point3D outsideHitPoint = _hitObjects[0]->hit(refracted.getRay());
//
//    RenderRay directLightRay = getDirectLight(outsideHitPoint, _hitObjects[0], objects, _lights);
//    RenderRay reflexionsLightRay = getReflexionsLight(refracted.getRay(), objects, _hitObjects[0], bounces);
//    RenderRay diffuseLightRay = getDiffuseLight(outsideHitPoint, _hitObjects[0], objects, _lights, 10, bounces);
//    RenderRay refractionsLightRay = getRefractionsLight(outsideHitPoint, refracted.getRay(), objects, bounces, _hitObjects[0]);
//
//    RenderRay finalRay = directLightRay + reflexionsLightRay + diffuseLightRay + refractionsLightRay;
//
//    return finalRay;
//}
