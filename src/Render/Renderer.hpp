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
#include "RenderData.hpp"

namespace raytracer
{
    class Renderer
    {
        public:
            Renderer(Camera camera) : camera(camera) {}
            ~Renderer();

            void addObject(const std::shared_ptr<IObject>& object);
            void addLight(const std::shared_ptr<ILight>& light);

            std::vector<Chunk> getChunks(int chunkSizeX, int chunkSizeY);

            void renderChunk(const Chunk &chunk);

            raytracer::RenderRay traceRay(int x, int y);

            static Vector3D getRandomRayFromCone(const Vector3D &normal, double angle);

            static RenderRay getDirectLight(const RenderPoint &point, const RenderData &data);
            RenderRay getReflexionsLight(const RenderPoint &point, const RenderData &data, size_t bounces);
            RenderRay getDiffuseLight(const RenderPoint &point, const RenderData &data, size_t bounces);
            RenderRay getRefractionsLight(const RenderPoint &point, const RenderData &data, size_t bounces);

            Camera camera;
            RenderData renderData;
            double cameraExposure = 2;
    };
}
