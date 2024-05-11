/*
** EPITECH PROJECT, 2024
** Color.hpp
** File description:
** raytracer
*/

#pragma once

#include <cmath>

namespace raytracer
{
    class Color {
        public:
            Color(double r = 0, double g = 0, double b = 0) : r(r), g(g), b(b) {}
            ~Color();

            double r;
            double g;
            double b;

            Color operator+(const Color& other) const {return {r + other.r, g + other.g, b + other.b};}

            Color operator*(const Color& other) const {return {r * other.r, g * other.g, b * other.b};}

            Color operator*(double scalar) const {return {r * scalar, g * scalar, b * scalar};}

            Color operator/(double scalar) const {return {r / scalar, g / scalar, b / scalar};}

            Color operator-(const Color& other) const {return {r - other.r, g - other.g, b - other.b};}

            Color operator+=(const Color& other);

            void cap();

            void normalize();
    };
}
