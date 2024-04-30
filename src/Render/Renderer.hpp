/*
** EPITECH PROJECT, 2024
** Renderer.hpp
** File description:
** raytracer
*/

#pragma once

#include "../Objects/IObject.hpp"
#include "Camera.hpp"
#include "../sfml/sfml.hpp"
#include "../Light/ILight.hpp"
#include "RenderRay.hpp"

namespace raytracer
{
    class Renderer
    {
        public:
            Renderer(Camera camera) : camera(camera) {}
            ~Renderer();

            void addObject(std::shared_ptr<IObject> object);
            void addLight(std::shared_ptr<ILight> light);

            raytracer::RenderRay traceRay(int x, int y);
            void renderImage();
            std::vector<std::shared_ptr<IObject>> objects;

            RenderRay getReflexionsLight(const Ray3D &ray, const std::vector<std::shared_ptr<IObject>> &objects,
                                         std::shared_ptr<IObject> object, int bounces);
            RenderRay getDirectLight(const Point3D hit_point, const std::shared_ptr<IObject> object,
                                     const std::vector<std::shared_ptr<IObject>> &objects,
                                     const std::vector<std::shared_ptr<ILight>> &lights);
            RenderRay getDiffuseLight(const Point3D hit_point, const std::shared_ptr<IObject> object,
                                      const std::vector<std::shared_ptr<IObject>> &objects,
                                      const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces);
            RenderRay getRefractionsLight(Point3D hitPoint, const Ray3D &ray,
                                          const std::vector<std::shared_ptr<IObject>> &objects, int bounces,
                                          std::shared_ptr<IObject> object);

            static RenderRay getRandomRay(const Point3D &origin, const std::shared_ptr<IObject> object);
            static Color getColorFromLight(const RenderRay &ray, double max_intensity);
            Camera camera;
        private:
            Ray3D _currentRay;
            std::vector<std::shared_ptr<IObject>> _hitObjects;
            std::vector<std::shared_ptr<ILight>> _lights;

            int maxBounces = 2;
            int maxDiffuseBounces = 2;

            int diffuseReflexionRays = 20;

            double cameraExposure = 2;

            void _sortHitObjectsByContactDistance();
    };
}
