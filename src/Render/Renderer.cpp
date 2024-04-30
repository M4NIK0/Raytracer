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
//    RenderRay reflexionsLight = getReflexionsLight(point, _renderData, _renderData.maxBounces);
//    RenderRay diffuseLight = getDiffuseLight(point, _renderData, _renderData.maxBounces);
//    RenderRay refractionsLight = getRefractionsLight(point, _renderData, _renderData.maxBounces);

    RenderRay finalRay = directLight;// + reflexionsLight + diffuseLight + refractionsLight;

    return finalRay;
}

//raytracer::RenderRay
//raytracer::Renderer::getReflexionsLight(const Ray3D &ray, const std::vector<std::shared_ptr<IObject>> &objects,
//                                        std::shared_ptr<IObject> object, int bounces)
//{
//    if (object->getReflexionIndex(ray) == 0.0)
//    {
//        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
//    }
//
//    if (bounces <= 0)
//    {
//        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
//    }
//
//    if (!object)
//    {
//        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
//    }
//
//    Point3D hitPoint = object->hit(ray);
//    Vector3D normal = object->getNormalFromPoint(hitPoint);
//    normal.normalize();
//
//    Ray3D reflectedRay = object->hitReflectedRay(ray);
//
//    _hitObjects.clear();
//
//    for (auto &obj: objects)
//    {
//        if (obj == object)
//            continue;
//        if (obj->hits(reflectedRay))
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
//    RenderRay directLightRay = getDirectLight(_hitObjects[0]->hit(reflectedRay), _hitObjects[0], objects, _lights);
//    RenderRay reflexionsLightRay = getReflexionsLight(reflectedRay, objects, _hitObjects[0], (bounces - 1));
//    RenderRay diffuseLightRay = getDiffuseLight(_hitObjects[0]->hit(reflectedRay), _hitObjects[0], objects, _lights, 100, (bounces - 1));
//    RenderRay refractionsLightRay = getRefractionsLight(_hitObjects[0]->hit(reflectedRay), reflectedRay, objects, (bounces - 1), _hitObjects[0]);
//
//    RenderRay finalRay = directLightRay + reflexionsLightRay + diffuseLightRay + refractionsLightRay;
//
//    finalRay.color = finalRay.color * object->getReflexionIndex(ray);
//
//    return finalRay;
//}

//raytracer::RenderRay
//raytracer::Renderer::getDiffuseLight(const Point3D hit_point, const std::shared_ptr<IObject> object,
//                                     const std::vector<std::shared_ptr<IObject>> &objects,
//                                     const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces)
//{
//    std::vector <RenderRay> diffuseLightRays;
//
//    if (bounces <= 0)
//    {
//        return RenderRay();
//    }
//
//    for (int i = 0; i < rays; ++i)
//    {
//        RenderRay currentRay = getRandomRay(hit_point, object);
//
//        _hitObjects.clear();
//        for (auto &obj : objects)
//        {
//            if (obj == object && object->getNormalFromPoint(hit_point).dot(currentRay.direction) > 0)
//                continue;
//
//            if (obj->hits(currentRay))
//                _hitObjects.push_back(obj);
//        }
//
//        if (_hitObjects.empty())
//            continue;
//
//        _sortHitObjectsByContactDistance();
//
//        Point3D contactPoint = _hitObjects[0]->hit(currentRay);
//        double distance = Point3D::distance(currentRay.origin, contactPoint);
//
//        RenderRay directLight = getDirectLight(contactPoint, _hitObjects[0], objects, lights);
//        RenderRay diffuseLight = getDiffuseLight(contactPoint, _hitObjects[0], objects, lights, rays, (bounces - 1));
//
//        currentRay.color = (directLight.color + diffuseLight.color) * object->getSurfaceAbsorbtion();
//
//        diffuseLightRays.push_back(currentRay);
//    }
//
//    RenderRay finalRay = RenderRay();
//    for (auto ray : diffuseLightRays)
//    {
//        finalRay.color = finalRay.color + ray.color;
//    }
//
//    finalRay.color = finalRay.color * (1.0 / rays);
//
//    return finalRay;
//}

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

            // If the shadow ray hits something before reaching the light source, continue to the next light source
            if (point.hitsSomething(data.objects, shadowRay))
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

//raytracer::RenderRay
//raytracer::Renderer::getRandomRay(const raytracer::Point3D &origin, const std::shared_ptr<IObject> object)
//{
//    if (!object)
//    {
//        return RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
//    }
//
//    double x = (double) rand() / RAND_MAX;
//    double y = (double) rand() / RAND_MAX;
//    double z = (double) rand() / RAND_MAX;
//
//    Vector3D randomDirection = Vector3D(x, y, z);
//    randomDirection = randomDirection.normalize();
//
//    Vector3D normal = object->getNormalFromPoint(origin);
//    double normalCompute = normal.dot(randomDirection);
//
//    if (normalCompute < 0)
//    {
//        randomDirection = randomDirection * -1;
//    }
//
//    return RenderRay(Ray3D(origin, randomDirection));
//}

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
