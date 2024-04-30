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
#include "RenderPoint.hpp"

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

            RenderRay getReflexionsLight(const RenderPoint &point, const std::vector<std::shared_ptr<IObject>> &objects,
                                         int bounces);

            RenderRay getDirectLight(const RenderPoint &point, const std::vector<std::shared_ptr<IObject>> &objects,
                                     const std::vector<std::shared_ptr<ILight>> &lights);

            RenderRay getDiffuseLight(const RenderPoint &point, const std::vector<std::shared_ptr<IObject>> &objects,
                                      const std::vector<std::shared_ptr<ILight>> &lights, int rays, int bounces);

            RenderRay getRefractionsLight(const RenderPoint &point, const std::vector<std::shared_ptr<IObject>> &objects,
                                          int bounces);

            static RenderRay getRandomRay(const RenderPoint &point);

            Camera camera;
        private:
            std::vector<std::shared_ptr<ILight>> _lights;

            int maxBounces = 2;
            int maxDiffuseBounces = 2;

            int diffuseReflexionRays = 20;

            double cameraExposure = 2;

            void _sortHitObjectsByContactDistance();
    };
}
