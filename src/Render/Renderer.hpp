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
            Renderer(Camera camera) : _camera(camera) {}
            ~Renderer();

            void addObject(std::shared_ptr<IPrimitive> object);
            void addLight(std::shared_ptr<ILight> light);

            raytracer::Color traceRay(int x, int y);
            void renderImage();
            std::vector<std::shared_ptr<IPrimitive>> objects;

            static RenderRay getReflexionsLight(const Ray3D &ray, const std::vector<std::shared_ptr<IPrimitive>> &objects, int bounces);
            static RenderRay getSurfaceLight(const Point3D hit_point, const std::shared_ptr<IPrimitive> &object,
                                             const std::vector<std::shared_ptr<IPrimitive>> &objects,
                                             const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces);
        private:
            Camera _camera;
            Ray3D _currentRay;
            std::vector<std::shared_ptr<IPrimitive>> _hitObjects;
            std::vector<std::shared_ptr<ILight>> _lights;

            int maxBounces = 2;
            int maxDiffuseBounces = 2;

            int diffuseReflexionRays = 20;

            void _sortHitObjectsByContactDistance();
    };
}
