/*
** EPITECH PROJECT, 2024
** Camera.hpp
** File description:
** raytracer
*/

#pragma once

#include "../Math/Ray3D.hpp"
#include "../Math/Rectangle3D.hpp"

namespace raytracer
{
    class Camera
    {
        public:
            Camera(Point3D origin, Rectangle3D screen, int width, int height) : _origin(origin), _screen(screen), _width(width), _height(height) {}
            ~Camera();

            Ray3D getRay(int x, int y);

        private:
            Rectangle3D _screen;
            int _width;
            int _height;
            Point3D _origin;
    };
}
