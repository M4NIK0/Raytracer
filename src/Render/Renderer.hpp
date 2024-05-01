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
    class Chunk
    {
        public:
            Chunk(size_t x, size_t y, size_t width, size_t height) : x(x), y(y), width(width), height(height) {}
            ~Chunk() = default;

            size_t x;
            size_t y;
            size_t width;
            size_t height;
    };

    class renderData
    {
        public:
            renderData() = default;
            ~renderData() = default;

            std::vector<std::shared_ptr<IObject>> objects = {};
            std::vector<std::shared_ptr<ILight>> lights = {};

            size_t diffuseRays = 10;
            size_t reflexionsRays = 5;
            size_t maxBounces = 2;

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

            std::vector<std::vector<RenderRay>> renderChunks(const Chunk &chunk);

            raytracer::RenderRay traceRay(int x, int y);

            static Vector3D getRandomRayFromCone(const Vector3D &normal, double angle);

            RenderRay getDirectLight(const RenderPoint &point, const renderData &data);
            RenderRay getReflexionsLight(const RenderPoint &point, const renderData &data, int bounces);
            RenderRay getDiffuseLight(const RenderPoint &point, const renderData &data, int bounces);
//            RenderRay getRefractionsLight(const RenderPoint &point, const renderData &data, int bounces);
//            static RenderRay getRandomRay(const RenderPoint &point);

            Camera camera;
        private:
            renderData _renderData;

            double cameraExposure = 2;
    };
}
