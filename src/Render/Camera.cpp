/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** raytracer
*/

#include "Camera.hpp"
#include "../Math/Matrix.hpp"

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
    origin = origin + direction;
    _screen.move(direction);
}

void raytracer::Camera::rotate(raytracer::Vector3D direction)
{
    // Convert the rotation angles from degrees to radians
    double thetaX = direction.x * M_PI / 180.0;
    double thetaY = direction.y * M_PI / 180.0;
    double thetaZ = direction.z * M_PI / 180.0;

    Vector3D bottomVector = _screen.bottom_side;
    Vector3D leftVector = _screen.left_side;

    Matrix rotationX(3, 3);
    rotationX = std::vector<std::vector<double>>{
        {1, 0, 0},
        {0, cos(thetaX), -sin(thetaX)},
        {0, sin(thetaX), cos(thetaX)}
    };

    Matrix rotationY(3, 3);
    rotationY = std::vector<std::vector<double>>{
        {cos(thetaY), 0, sin(thetaY)},
        {0, 1, 0},
        {-sin(thetaY), 0, cos(thetaY)}
    };

    Matrix rotationZ(3, 3);
    rotationZ = std::vector<std::vector<double>>{
        {cos(thetaZ), -sin(thetaZ), 0},
        {sin(thetaZ), cos(thetaZ), 0},
        {0, 0, 1}
    };

    Matrix bottomMatrix(3, 1);
    bottomMatrix = std::vector<std::vector<double>>{
        {bottomVector.x},
        {bottomVector.y},
        {bottomVector.z}
    };

    Matrix leftMatrix(3, 1);
    leftMatrix = std::vector<std::vector<double>>{
        {leftVector.x},
        {leftVector.y},
        {leftVector.z}
    };

    // rotate vectors around origin
    Matrix bottomResult = rotationX * bottomMatrix;
    bottomResult = rotationY * bottomResult;
    bottomResult = rotationZ * bottomResult;

    Matrix leftResult = rotationX * leftMatrix;
    leftResult = rotationY * leftResult;
    leftResult = rotationZ * leftResult;

    _screen.bottom_side = Vector3D(bottomResult.get(0, 0), bottomResult.get(1, 0), bottomResult.get(2, 0));
    _screen.left_side = Vector3D(leftResult.get(0, 0), leftResult.get(1, 0), leftResult.get(2, 0));

    // get the center of the rectangle
    Point3D center = _screen.origin + _screen.bottom_side * 0.5 + _screen.left_side * 0.5;

    // get the vector between the camera origin and the center of the rectangle
    Vector3D originToCenter = center - origin;

    // rotate this vector
    Matrix originToCenterMatrix(3, 1);
    originToCenterMatrix = std::vector<std::vector<double>>{
        {originToCenter.x},
        {originToCenter.y},
        {originToCenter.z}
    };

    Matrix originToCenterResult = rotationX * originToCenterMatrix;
    originToCenterResult = rotationY * originToCenterResult;
    originToCenterResult = rotationZ * originToCenterResult;

    originToCenter = Vector3D(originToCenterResult.get(0, 0), originToCenterResult.get(1, 0), originToCenterResult.get(2, 0));

    // apply coordinates to the rectangle center
    center = origin + originToCenter;

    // apply the transform to the rectangle origin to match the center
    _screen.origin = center - _screen.bottom_side * 0.5 - _screen.left_side * 0.5;
}