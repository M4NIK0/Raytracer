/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** raytracer
*/

#include "Camera.hpp"

raytracer::Camera::~Camera() = default;

raytracer::Ray3D raytracer::Camera::getRay(int x, int y)
{
    double u = (double)x / (double)width;
    double v = (double)y / (double)height;
    Point3D point = _screen.pointAt(u, v);
    Vector3D direction = point - origin;
    return Ray3D(origin, direction);
}

void raytracer::Camera::move(raytracer::Vector3D direction)
{

}

void raytracer::Camera::rotate(raytracer::Vector3D direction)
{
    _screen.move(direction);
    _rotation = _rotation + direction;
}
