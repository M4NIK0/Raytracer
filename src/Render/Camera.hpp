/*
** EPITECH PROJECT, 2024
** Camera.hpp
** File description:
** raytracer
*/

#pragma once

#include "Ray3D.hpp"
#include "../Math/Rectangle3D.hpp"

namespace raytracer
{
    class Camera
    {
        public:
            Camera(Point3D origin, Rectangle3D screen, int width, int height) : origin(origin), _screen(screen), width(width), height(height) {}
            ~Camera();

            Ray3D getRay(int x, int y);

            Point3D origin;

            int width;
            int height;
        private:
            Rectangle3D _screen;
    };
}
