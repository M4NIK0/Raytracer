/*
** EPITECH PROJECT, 2024
** Renderer.hpp
** File description:
** raytracer
*/

#pragma once

#include "../Primitives/IPrimitive.hpp"
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

            void addObject(std::shared_ptr<IPrimitive> object);
            void addLight(std::shared_ptr<ILight> light);

            raytracer::RenderRay traceRay(int x, int y);
            void renderImage();
            std::vector<std::shared_ptr<IPrimitive>> objects;

            RenderRay getReflexionsLight(const Ray3D &ray, const std::vector<std::shared_ptr<IPrimitive>> &objects, int bounces);
            RenderRay getSurfaceLight(const Point3D hit_point, const std::shared_ptr<IPrimitive> object,
                                      const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                      const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces);

            RenderRay getDirectLight(const Point3D hit_point, const std::shared_ptr<IPrimitive> object,
                                     const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                     const std::vector<std::shared_ptr<ILight>> &lights);
            RenderRay getDiffuseLight(const Point3D hit_point, const std::shared_ptr<IPrimitive> object,
                                      const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                      const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces);

            static RenderRay getRandomRay(const Point3D &origin, const std::shared_ptr<IPrimitive> &object);
            static Color getColorFromLight(const RenderRay &ray, double max_intensity);
            Camera camera;
        private:
            Ray3D _currentRay;
            std::vector<std::shared_ptr<IPrimitive>> _hitObjects;
            std::vector<std::shared_ptr<ILight>> _lights;

            int maxBounces = 2;
            int maxDiffuseBounces = 2;

            int diffuseReflexionRays = 20;

            double cameraExposure = 2;

            void _sortHitObjectsByContactDistance();
    };
}
