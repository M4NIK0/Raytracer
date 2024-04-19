/*
** EPITECH PROJECT, 2024
** Rectangle3D.cpp
** File description:
** raytracer
*/

#include "Rectangle3D.hpp"
#include "Matrix.hpp"

raytracer::Rectangle3D::~Rectangle3D() = default;

raytracer::Point3D raytracer::Rectangle3D::pointAt(double u, double v) const
{
    return origin + bottom_side * u + left_side * v;
}

void raytracer::Rectangle3D::move(raytracer::Vector3D direction)
{
    // move cam taking into account the rotation
    origin = origin + direction;
}

void raytracer::Rectangle3D::rotate(raytracer::Vector3D direction)
{
    // Rotate the origin around the center and the vectors, then update the vectors

    Point3D center = origin + bottom_side * 0.5 + left_side * 0.5;

    Matrix rotationX(3, 3);
    rotationX = std::vector<std::vector<double>>{
        {1, 0, 0},
        {0, cos(direction.x), -sin(direction.x)},
        {0, sin(direction.x), cos(direction.x)}
    };

    Matrix rotationY(3, 3);
    rotationY = std::vector<std::vector<double>>{
        {cos(direction.y), 0, sin(direction.y)},
        {0, 1, 0},
        {-sin(direction.y), 0, cos(direction.y)}
    };

    Matrix rotationZ(3, 3);
    rotationZ = std::vector<std::vector<double>>{
        {cos(direction.z), -sin(direction.z), 0},
        {sin(direction.z), cos(direction.z), 0},
        {0, 0, 1}
    };

    Matrix originMatrix(3, 1);
    originMatrix = std::vector<std::vector<double>>{
        {origin.x},
        {origin.y},
        {origin.z}
    };

    Matrix centerMatrix(3, 1);
    centerMatrix = std::vector<std::vector<double>>{
        {center.x},
        {center.y},
        {center.z}
    };

    Matrix bottomSideMatrix(3, 1);
    bottomSideMatrix = std::vector<std::vector<double>>{
        {bottom_side.x},
        {bottom_side.y},
        {bottom_side.z}
    };

    Matrix leftSideMatrix(3, 1);
    leftSideMatrix = std::vector<std::vector<double>>{
        {left_side.x},
        {left_side.y},
        {left_side.z}
    };

    originMatrix = rotationX * originMatrix;
    originMatrix = rotationY * originMatrix;
    originMatrix = rotationZ * originMatrix;

    centerMatrix = rotationX * centerMatrix;
    centerMatrix = rotationY * centerMatrix;
    centerMatrix = rotationZ * centerMatrix;

    bottomSideMatrix = rotationX * bottomSideMatrix;
    bottomSideMatrix = rotationY * bottomSideMatrix;
    bottomSideMatrix = rotationZ * bottomSideMatrix;

    leftSideMatrix = rotationX * leftSideMatrix;
    leftSideMatrix = rotationY * leftSideMatrix;
    leftSideMatrix = rotationZ * leftSideMatrix;

    origin = Point3D(originMatrix.get(0, 0), originMatrix.get(1, 0), originMatrix.get(2, 0));
    center = Point3D(centerMatrix.get(0, 0), centerMatrix.get(1, 0), centerMatrix.get(2, 0));
    bottom_side = Vector3D(bottomSideMatrix.get(0, 0), bottomSideMatrix.get(1, 0), bottomSideMatrix.get(2, 0));
    left_side = Vector3D(leftSideMatrix.get(0, 0), leftSideMatrix.get(1, 0), leftSideMatrix.get(2, 0));

    origin.x = origin.x - center.x;
    origin.y = origin.y - center.y;
    origin.z = origin.z - center.z;

    bottom_side.x = bottom_side.x - center.x;
    bottom_side.y = bottom_side.y - center.y;
    bottom_side.z = bottom_side.z - center.z;

    left_side.x = left_side.x - center.x;
    left_side.y = left_side.y - center.y;
    left_side.z = left_side.z - center.z;
}
