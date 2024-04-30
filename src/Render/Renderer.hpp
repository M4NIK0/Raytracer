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
    class renderData
    {
        public:
            renderData() = default;
            ~renderData() = default;

            std::vector<std::shared_ptr<IObject>> objects;
            std::vector<std::shared_ptr<ILight>> lights;

            size_t diffuseRays = 20;
            size_t reflexionsRays = 20;
            size_t maxBounces = 4;

            size_t width = 1920;
            size_t height = 1080;

            size_t chunks_x = 10;
            size_t chunks_y = 10;
    };

    class Renderer
    {
        public:
            Renderer(Camera camera) : camera(camera) {}
            ~Renderer();

            void addObject(std::shared_ptr<IObject> object);
            void addLight(std::shared_ptr<ILight> light);

            raytracer::RenderRay traceRay(int x, int y);

            RenderRay getDirectLight(const RenderPoint &point, const renderData &data);
//            RenderRay getReflexionsLight(const RenderPoint &point, const renderData &data, int bounces);
//            RenderRay getDiffuseLight(const RenderPoint &point, const renderData &data, int bounces);
//            RenderRay getRefractionsLight(const RenderPoint &point, const renderData &data, int bounces);
//            static RenderRay getRandomRay(const RenderPoint &point);

            Camera camera;
        private:
            renderData _renderData;

            double cameraExposure = 2;

            void _sortHitObjectsByContactDistance();
    };
}
