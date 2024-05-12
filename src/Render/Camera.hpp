/*
** EPITECH PROJECT, 2024
** Camera.hpp
** File description:
** raytracer
*/

#pragma once

#include "../../include/Math/Ray3D.hpp"
#include "../../include/Math/Rectangle3D.hpp"

namespace raytracer
{
    class Camera
    {
        public:
            Camera(Point3D origin, Rectangle3D screen, int width, int height) : origin(origin), width(width), height(height), _screen(screen) {}
            Camera(int width, int height, double fov);
            ~Camera();

            Ray3D getRay(int x, int y);

            Point3D origin;

            int width;
            int height;

            double exposure = 1.0;
            double sensitivity = 100;

            void move(Vector3D direction);
            void rotate(Vector3D direction);

        private:
            Rectangle3D _screen;
            Vector3D _rotation;
    };
}
