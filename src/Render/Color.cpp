/*
** EPITECH PROJECT, 2024
** Color.cpp
** File description:
** raytracer
*/

#include "Color.hpp"

raytracer::Color::~Color() = default;

raytracer::Color raytracer::Color::operator+=(const raytracer::Color &other)
{
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

void raytracer::Color::cap()
{
    r = r > 255 ? 255 : r;
    g = g > 255 ? 255 : g;
    b = b > 255 ? 255 : b;

    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;
}

void raytracer::Color::normalize()
{
    double size = sqrt(r * r + g * g + b * b);
    r = (r / size);
    g = (g / size);
    b = (b / size);
}
