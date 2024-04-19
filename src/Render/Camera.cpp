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
    // Convert the rotation angles from degrees to radians
    double thetaX = direction.x * M_PI / 180.0;
    double thetaY = direction.y * M_PI / 180.0;
    double thetaZ = direction.z * M_PI / 180.0;

    // Create rotation matrices
    Matrix rotationX = {
        {1, 0, 0},
        {0, cos(thetaX), -sin(thetaX)},
        {0, sin(thetaX), cos(thetaX)}
    };

    Matrix rotationY = {
        {cos(thetaY), 0, sin(thetaY)},
        {0, 1, 0},
        {-sin(thetaY), 0, cos(thetaY)}
    };

    Matrix rotationZ = {
        {cos(thetaZ), -sin(thetaZ), 0},
        {sin(thetaZ), cos(thetaZ), 0},
        {0, 0, 1}
    };

    // Rotate the origin
    origin = rotationX * rotationY * rotationZ * origin;

    // Rotate the screen
    _screen.rotate(rotationX * rotationY * rotationZ);
}
