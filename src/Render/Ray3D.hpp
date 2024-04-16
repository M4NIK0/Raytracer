/*
** EPITECH PROJECT, 2024
** Ray3D.hpp
** File description:
** raytracer
*/

#pragma once

#include "../Math/Point3D.hpp"
#include "../Math/Vector3D.hpp"
#include "../sfml/sfml.hpp"

namespace raytracer
{
    class Ray3D
    {
        public:
            Ray3D() = default;
            Ray3D(const Point3D &origin, const Vector3D &direction) : origin(origin), direction(direction) {};
            ~Ray3D();

            friend std::ostream& operator<<(std::ostream& os, const Ray3D& r) { os << "Ray3D(" << r.origin << ", " << r.direction << ")"; return os; }

            Ray3D& operator=(const Ray3D& other);

            Point3D origin;
            Vector3D direction;

            Color getColor();

            Color objectColor = {0, 0, 0};
            std::vector<Color> colors;
            std::vector<double> colorAmounts;
            std::vector<Point3D> hitPositions;
    };
}
