/*
** EPITECH PROJECT, 2024
** Point3D.cpp
** File description:
** raytracer
*/

#include <cmath>
#include "../include/Point3D.hpp"

raytracer::Point3D &raytracer::Point3D::operator=(const raytracer::Point3D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

raytracer::Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
raytracer::Point3D::Point3D(const raytracer::Point3D &other) : x(other.x), y(other.y), z(other.z) {};

raytracer::Point3D::Point3D(raytracer::Point3D &&other) : x(other.x), y(other.y), z(other.z) {}

raytracer::Point3D::Point3D(raytracer::Vector3D vector3D) : x(vector3D.x), y(vector3D.y), z(vector3D.z) {}

std::ostream &raytracer::operator<<(std::ostream &os, const raytracer::Point3D &p)
{
    os << "Point3D(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}

raytracer::Point3D raytracer::Point3D::operator+(const raytracer::Vector3D &vector) const
{
    return Point3D(x + vector.x, y + vector.y, z + vector.z);
}

raytracer::Point3D raytracer::Point3D::operator-(const raytracer::Vector3D &vector) const
{
    return Point3D(x - vector.x, y - vector.y, z - vector.z);
}

raytracer::Vector3D raytracer::Point3D::operator-(const raytracer::Point3D &other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

bool raytracer::Point3D::operator==(const raytracer::Point3D &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

double raytracer::Point3D::distance(raytracer::Point3D a, raytracer::Point3D b)
{
    return (a - b).length();
}

// Function to rotate a point around a center
raytracer::Point3D raytracer::Point3D::rotateAroundCenter(Point3D &point, Point3D &center, double rx, double ry, double rz) {
    Point3D newPoint = point;

    // Convert the rotation angles from degrees to radians
    rx = rx * M_PI / 180.0;
    ry = ry * M_PI / 180.0;
    rz = rz * M_PI / 180.0;

    // create rotation matrix
    Matrix rotationMatrixX;
    rotationMatrixX = {
        {1, 0, 0},
        {0, cos(rx), -sin(rx)},
        {0, sin(rx), cos(rx)}
    };

    Matrix rotationMatrixY;
    rotationMatrixY = {
        {cos(ry), 0, sin(ry)},
        {0, 1, 0},
        {-sin(ry), 0, cos(ry)}
    };

    Matrix rotationMatrixZ;
    rotationMatrixZ = {
        {cos(rz), -sin(rz), 0},
        {sin(rz), cos(rz), 0},
        {0, 0, 1}
    };

    // Cancel point translation
    newPoint = newPoint - center;

    // Rotate the point around the center
    newPoint = {
        newPoint.x * rotationMatrixX[0][0] + newPoint.y * rotationMatrixX[0][1] + newPoint.z * rotationMatrixX[0][2],
        newPoint.x * rotationMatrixX[1][0] + newPoint.y * rotationMatrixX[1][1] + newPoint.z * rotationMatrixX[1][2],
        newPoint.x * rotationMatrixX[2][0] + newPoint.y * rotationMatrixX[2][1] + newPoint.z * rotationMatrixX[2][2]
    };

    newPoint = {
        newPoint.x * rotationMatrixY[0][0] + newPoint.y * rotationMatrixY[0][1] + newPoint.z * rotationMatrixY[0][2],
        newPoint.x * rotationMatrixY[1][0] + newPoint.y * rotationMatrixY[1][1] + newPoint.z * rotationMatrixY[1][2],
        newPoint.x * rotationMatrixY[2][0] + newPoint.y * rotationMatrixY[2][1] + newPoint.z * rotationMatrixY[2][2]
    };

    newPoint = {
        newPoint.x * rotationMatrixZ[0][0] + newPoint.y * rotationMatrixZ[0][1] + newPoint.z * rotationMatrixZ[0][2],
        newPoint.x * rotationMatrixZ[1][0] + newPoint.y * rotationMatrixZ[1][1] + newPoint.z * rotationMatrixZ[1][2],
        newPoint.x * rotationMatrixZ[2][0] + newPoint.y * rotationMatrixZ[2][1] + newPoint.z * rotationMatrixZ[2][2]
    };

    // Add the translation back
    newPoint.x += center.x;
    newPoint.y += center.y;
    newPoint.z += center.z;

    return newPoint;
}
