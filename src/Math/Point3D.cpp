/*
** EPITECH PROJECT, 2024
** Point3D.cpp
** File description:
** raytracer
*/

#include "Point3D.hpp"

raytracer::Point3D &raytracer::Point3D::operator=(const raytracer::Point3D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

#include <cmath>

// Function to rotate a point around a center
raytracer::Point3D raytracer::Point3D::rotateAroundCenter(Point3D &point, Point3D &center, double rx, double ry, double rz) {
    Point3D newPoint = point;

    // Convert the rotation angles from degrees to radians
    rx = rx * M_PI / 180.0;
    ry = ry * M_PI / 180.0;
    rz = rz * M_PI / 180.0;

    // Translate point back to origin
    newPoint.x -= center.x;
    newPoint.y -= center.y;
    newPoint.z -= center.z;

    // Rotate around x-axis
    double y = newPoint.y*cos(rx) - newPoint.z*sin(rx);
    double z = newPoint.y*sin(rx) + newPoint.z*cos(rx);
    point.y = y;
    point.z = z;

    // Rotate around y-axis
    double x = newPoint.x*cos(ry) + newPoint.z*sin(ry);
    z = -point.x*sin(ry) + newPoint.z*cos(ry);
    newPoint.x = x;
    newPoint.z = z;

    // Rotate around z-axis
    x = newPoint.x*cos(rz) - newPoint.y*sin(rz);
    y = newPoint.x*sin(rz) + newPoint.y*cos(rz);
    newPoint.x = x;
    newPoint.y = y;

    // Translate point back
    newPoint.x += center.x;
    newPoint.y += center.y;
    newPoint.z += center.z;

    return newPoint;
}