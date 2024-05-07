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
#include <chrono>

namespace raytracer
{
    class Renderer
    {
        public:
            class Error : public std::exception
            {
                public:
                    Error(std::string const &message) noexcept
                        : _message(message) {}

                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message;
            };

            Renderer(Camera camera) : camera(camera) {}
            ~Renderer();

            void addObject(const std::shared_ptr<IObject>& object);
            void addLight(const std::shared_ptr<ILight>& light);

            std::vector<Chunk> getChunks(int chunkSizeX, int chunkSizeY);

            void renderChunk(const Chunk &chunk);

            raytracer::RenderRay traceRay(int x, int y);

            void stepMotions();

            static Vector3D getRandomRayFromCone(const Vector3D &normal, double angle);

            static RenderRay getDirectLight(const RenderPoint &point, const RenderData &data);
            static RenderRay getReflexionsLight(const RenderPoint &point, const RenderData &data, size_t bounces);
            static RenderRay getDiffuseLight(const RenderPoint &point, const RenderData &data, size_t bounces);
            static RenderRay getRefractionsLight(const RenderPoint &point, const RenderData &data, size_t bounces);

            Camera camera;
            RenderData renderData;
            double cameraExposure = 2;
    };
}
