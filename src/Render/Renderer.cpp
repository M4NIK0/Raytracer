/*
** EPITECH PROJECT, 2024
** Renderer.cpp
** File description:
** raytracer
*/

#include <vector>
#include <algorithm>
#include <random>
#include "Renderer.hpp"
#include "RenderRay.hpp"
#include "RenderPoint.hpp"

raytracer::Renderer::~Renderer() = default;

void raytracer::Renderer::addObject(const std::shared_ptr<IObject>& object)
{
    renderData.objects.push_back(object);
}

void raytracer::Renderer::addLight(const std::shared_ptr<ILight>& light)
{
    renderData.lights.push_back(light);
}

std::vector<raytracer::Chunk> raytracer::Renderer::getChunks(int chunkSizeX, int chunkSizeY)
{
    std::vector<Chunk> chunks;

    int x_max = 0;
    int y_max;

    while (x_max < renderData.width)
    {
        y_max = 0;
        while (y_max < renderData.height)
        {
            size_t x = x_max / chunkSizeX;
            size_t y = y_max / chunkSizeY;

            size_t width = chunkSizeX;
            size_t height = chunkSizeY;

            int x_rest = renderData.width - (x_max + chunkSizeX);
            int y_rest = renderData.height - (y_max + chunkSizeY);

            if (x_rest < 0)
            {
                width = chunkSizeX + x_rest;
            }

            if (y_rest < 0)
            {
                height = chunkSizeY + y_rest;
            }

            chunks.emplace_back(x, y, width, height);

            y_max += chunkSizeY;
        }

        x_max += chunkSizeX;
    }

    std::random_device rd;
    std::mt19937 g(rd());

//     Shuffle the chunks
    std::shuffle(chunks.begin(), chunks.end(), g);

    return chunks;
}

void raytracer::Renderer::renderChunk(const Chunk &chunk)
{
    for (int x = 0; x < chunk.width; x++)
    {
        for (int y = 0; y < chunk.height; y++)
        {
            Color tempColor = traceRay(x + (chunk.x * renderData.chunkWidth), y + (chunk.y * renderData.chunkHeight)).color / renderData.maxSamples;
            renderData.renderBuffer[x + (chunk.x * renderData.chunkWidth)][y + (chunk.y * renderData.chunkHeight)] += tempColor;
        }
    }
}

void raytracer::Renderer::render()
{

}

raytracer::RenderRay raytracer::Renderer::traceRay(int x, int y)
{
    Ray3D ray = camera.getRay(x, y);
    RenderPoint point;

    point.hitNearestObject(renderData.objects, ray);

    if (!point.object)
    {
        return {Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0))};
    }

    RenderRay directLight = getDirectLight(point, renderData);
    RenderRay reflexionsLight = getReflexionsLight(point, renderData, renderData.maxBounces);
    RenderRay diffuseLight = getDiffuseLight(point, renderData, renderData.maxBounces);
    RenderRay refractionsLight = getRefractionsLight(point, renderData, renderData.maxBounces);

    RenderRay finalRay = directLight + reflexionsLight + diffuseLight + refractionsLight;

    return finalRay;
}

raytracer::RenderRay raytracer::Renderer::traceEditorRay(int x, int y)
{
    Ray3D ray = camera.getRay(x, y);
    RenderPoint point;

    point.hitNearestObject(renderData.objects, ray);

    if (!point.object)
    {
        return {Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0))};
    }

    RenderRay directLight = getDirectLight(point, renderData);

    RenderRay finalRay = directLight;

    return finalRay;
}

void raytracer::Renderer::initMotions()
{
    for (auto &object: renderData.objects)
    {
        object->initiateMotion(camera.exposure, renderData.maxSamples);
    }
}

void raytracer::Renderer::stepMotions()
{
    for (auto &object: renderData.objects)
    {
        object->stepMotion();
    }
}

void raytracer::Renderer::resetMotions()
{
    for (auto &object: renderData.objects)
    {
        object->resetMotion();
    }
}

raytracer::Vector3D raytracer::Renderer::getRandomRayFromCone(const raytracer::Vector3D &normal, double angle)
{
    // Generate two random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double u = dis(gen);
    double v = dis(gen);

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
raytracer::Renderer::getDirectLight(const RenderPoint &point, const RenderData &data)
{
    // Get all direct light rays
    std::vector<RenderRay> directLightRays;

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));

    if (!point.object || point.object->getGlassState(point.hitPoint))
    {
        return ray;
    }

    for (auto &light: data.lights)
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
    for (const auto& lightRay: directLightRays)
    {
        ray.color = ray.color + lightRay.color;
    }

    ray.color = ray.color * point.object->getSurfaceAbsorbtion(point.hitPoint) * (1 - point.object->getReflexionIndex(point.hitPoint));
    return ray;
}

raytracer::RenderRay
raytracer::Renderer::getReflexionsLight(const RenderPoint &point, const RenderData &data, size_t bounces)
{
    if (bounces <= 0)
    {
        return {Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0))};
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
        return {Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0))};
    }

    // Get the direct light
    RenderRay directLight = getDirectLight(reflectionPoint, data);

    // Get the reflection light
    RenderRay reflectionLight = getReflexionsLight(reflectionPoint, data, bounces - 1);

    // Get the diffuse light
    RenderRay diffuseLight = getDiffuseLight(reflectionPoint, data, bounces - 1);

    // Get the refractions light
    RenderRay refractionsLight = getRefractionsLight(reflectionPoint, data, bounces - 1);

    // Get the emission light
    RenderRay emissionLight;
    emissionLight.color = point.object->getSurfaceEmission(point.hitPoint) * point.object->getSurfaceEmissionIntensity(point.hitPoint) * point.surfaceNormal.dot(reflection);

    // Mix the direct, reflection and diffuse light
    RenderRay ray = directLight + reflectionLight + diffuseLight + refractionsLight + emissionLight;

    ray.color = ray.color * point.object->getReflexionIndex(point.hitPoint);

    return ray;
}

raytracer::RenderRay raytracer::Renderer::getDiffuseLight(const RenderPoint &point, const RenderData &data, size_t bounces)
{
    if (bounces <= 0 || point.object->getGlassState(point.hitPoint))
    {
        return {Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0))};
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

        // Get the emission light
        RenderRay emissionLight;
        emissionLight.color = point.object->getSurfaceEmission(randomPoint.hitPoint) * point.object->getSurfaceEmissionIntensity(randomPoint.hitPoint) * point.surfaceNormal.dot(randomRay);

        // Mix the direct and diffuse light
        RenderRay ray = directLight + diffuseLight + reflectionLight + emissionLight;

        ray.color = ray.color * point.object->getSurfaceAbsorbtion(point.hitPoint);

        // Add the color of this ray to the total color
        totalColor = totalColor + ray.color;
    }

    RenderRay ray = RenderRay(Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0)));
    // Calculate the mean color
    ray.color = totalColor * (1.0 / data.diffuseRays) * (1 - point.object->getReflexionIndex(point.hitPoint));

    // Return a ray with the mean color
    return ray;
}

raytracer::RenderRay raytracer::Renderer::getRefractionsLight(const RenderPoint &point, const RenderData &data, size_t bounces)
{
    if (!point.object->getGlassState(point.hitPoint))
    {
        return {Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0))};
    }

    double refractionIndex = point.object->getRefractionIndex();

    double cosTheta1 = -point.surfaceNormal.dot(point.ray.direction);
    double eta = 1 / refractionIndex;  // Assuming the incident ray is in air or vacuum
    double k = 1 - eta * eta * (1 - cosTheta1 * cosTheta1);

    RenderRay refracted;

    if (k < 0)
    {
        return {Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0))};
    }
    else
    {
        refracted = RenderRay(Ray3D(point.hitPoint, (point.ray.direction * eta) + (point.surfaceNormal * (eta * cosTheta1 - sqrt(k)))));
    }

    refracted.origin = refracted.origin + refracted.direction * 0.1;
    Point3D exitPoint = point.object->hit(refracted.getRay());

    Vector3D normalExit = (point.object->getSurfaceNormal(exitPoint) * (-1));

    double cosTheta2 = -normalExit.dot(refracted.direction);
    double eta2 = refractionIndex;
    double k2 = 1 - eta2 * eta2 * (1 - cosTheta2 * cosTheta2);

    refracted = Ray3D(exitPoint - normalExit * 0.1, (refracted.direction * eta2) + (normalExit * (eta2 * cosTheta2 - sqrt(k2))));

    RenderPoint refractedPoint;
    refractedPoint.hitNearestObject(data.objects, refracted);

    if (!refractedPoint.object)
    {
        return {Ray3D(Point3D(0, 0, 0), Vector3D(0, 0, 0))};
    }

    RenderRay directLight = getDirectLight(refractedPoint, data);
    RenderRay reflectionLight = getReflexionsLight(refractedPoint, data, bounces);
    RenderRay diffuseLight = getDiffuseLight(refractedPoint, data, bounces);
    RenderRay refractionsLight = getRefractionsLight(refractedPoint, data, bounces);
    RenderRay emissionLight;
    emissionLight.color = point.object->getSurfaceEmission(point.hitPoint) * point.object->getSurfaceEmissionIntensity(point.hitPoint);

    RenderRay finalRay = directLight + reflectionLight + diffuseLight + refractionsLight + emissionLight;

    return finalRay;
}
