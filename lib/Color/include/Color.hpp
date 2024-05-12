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
            Color(double r = 0, double g = 0, double b = 0);
            ~Color();

            double r;
            double g;
            double b;

            Color operator+(const Color& other) const;

            Color operator*(const Color& other) const;

            Color operator*(double scalar) const;

            Color operator/(double scalar) const;

            Color operator-(const Color& other) const;

            Color operator+=(const Color& other);

            void cap();

            void normalize();
    };
}
