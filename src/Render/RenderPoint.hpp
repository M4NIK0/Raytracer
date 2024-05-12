/*
** EPITECH PROJECT, 2024
** RenderPoint.hpp
** File description:
** raytracer
*/

#pragma once

#include <memory>
#include "../../include/Math/Point3D.hpp"
#include "../../include/Math/Ray3D.hpp"
#include "../Objects/IObject.hpp"
#include "../../include/Color/Color.hpp"

namespace raytracer
{
    class RenderPoint
    {
        public:
            class Error : public std::exception
            {
                public:
                    Error(std::string const &message) :
                        _message(message) {};

                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message;
            };

            RenderPoint();

            ~RenderPoint();

            bool hitObject(std::shared_ptr<IObject> object, Ray3D &ray);
            void hitNearestObject(const std::vector<std::shared_ptr<IObject>> &objects, Ray3D &ray);
            bool hits(const std::shared_ptr<IObject> &object, const Ray3D &ray) const;
            bool hitsSomething(const std::vector<std::shared_ptr<IObject>> &objects, const Ray3D &ray) const;

            std::shared_ptr<IObject> object;
            Vector3D surfaceNormal;
            Vector3D volumeNormal;
            Ray3D ray;
            Point3D hitPoint;
            double distance;
    };
}
