/*
** EPITECH PROJECT, 2024
** RenderRay.hpp
** File description:
** raytracer
*/

#pragma once

#include "../../include/Math/Ray3D.hpp"
#include "../../include/Color/Color.hpp"

namespace raytracer
{
    class RenderRay : public Ray3D
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

            RenderRay(Point3D origin = {0, 0, 0}, Vector3D direction = {0, 0, 0});

            RenderRay(Ray3D ray) : Ray3D(ray.origin, ray.direction) {}

            ~RenderRay();

            Color getColor();

            RenderRay &operator=(const RenderRay &other)
            {
                origin = other.origin;
                direction = other.direction;
                color = other.color;
                return *this;
            }

            RenderRay &operator=(const Ray3D &other)
            {
                origin = other.origin;
                direction = other.direction;
                return *this;
            }

            RenderRay &operator+(const RenderRay &other)
            {
                color = color + other.color;
                return *this;
            }

            Ray3D getRay() { return Ray3D(origin, direction); }

            Color color = {0, 0, 0};
    };
}
