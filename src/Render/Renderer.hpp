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

    class RenderData
    {
        public:
            RenderData() = default;
            ~RenderData() = default;

            void initRenderBuffer();

            std::vector<std::shared_ptr<IObject>> objects = {};
            std::vector<std::shared_ptr<ILight>> lights = {};

            size_t diffuseRays = 20;
            size_t reflexionsRays = 5;
            size_t maxBounces = 2;

            std::vector<std::vector<Color>> renderBuffer = {};

            int width = 1920;
            int height = 1080;

            int chunkWidth = 100;
            int chunkHeight = 100;

            int maxSamples = 5;
    };

    class Renderer
    {
        public:
            Renderer(Camera camera) : camera(camera) {}
            ~Renderer();

            void addObject(std::shared_ptr<IObject> object);
            void addLight(std::shared_ptr<ILight> light);

            static std::vector<Chunk> getChunks(RenderData &data, int chunkSizeX, int chunkSizeY);

            void renderChunk(const Chunk &chunk, RenderData &data);

            raytracer::RenderRay traceRay(int x, int y);

            static Vector3D getRandomRayFromCone(const Vector3D &normal, double angle);

            RenderRay getDirectLight(const RenderPoint &point, const RenderData &data);
            RenderRay getReflexionsLight(const RenderPoint &point, const RenderData &data, int bounces);
            RenderRay getDiffuseLight(const RenderPoint &point, const RenderData &data, int bounces);
            RenderRay getRefractionsLight(const RenderPoint &point, const RenderData &data, int bounces);

            Camera camera;
            RenderData renderData;
            double cameraExposure = 2;
    };
}
