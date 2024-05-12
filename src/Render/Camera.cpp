/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** raytracer
*/

#include "Camera.hpp"
#include "../../include/Math/Matrix.hpp"

raytracer::Camera::Camera(int width, int height, double fov) : origin(Point3D(0.5, 0.5, 1)), width(width), height(height), _screen({{0, 1, 0}, {1, 0, 0}, {0, -1, 0}})
{
    int maxSize = std::max(width, height);
    double realWidth = (double)width / (double)maxSize;
    double realHeight = (double)height / (double)maxSize;

    _screen.origin = _screen.origin + _screen.bottom_side * 0.5 + _screen.left_side * 0.5;

    _screen.bottom_side = _screen.bottom_side * realWidth;
    _screen.left_side = _screen.left_side * realHeight;

    _screen.origin = _screen.origin - _screen.bottom_side * 0.5 - _screen.left_side * 0.5;

    double screenDistanceFromFOV = 1.0 / tan(fov * M_PI / 180.0 / 2);

    _screen.origin.z = origin.z - screenDistanceFromFOV;

    move(Vector3D(-0.5, -0.5, -1));
}

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
    // Convert the rotation angles from degrees to radians
    double thetaX = _rotation.x * M_PI / 180.0;
    double thetaY = _rotation.y * M_PI / 180.0;
    double thetaZ = _rotation.z * M_PI / 180.0;

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

    Matrix directionMatrix(3, 1);
    directionMatrix = std::vector<std::vector<double>>{
        {direction.x},
        {direction.y},
        {direction.z}
    };

    // rotate direction vector
    Matrix directionResult = rotationX * directionMatrix;
    directionResult = rotationY * directionResult;
    directionResult = rotationZ * directionResult;

    direction = Vector3D(directionResult.get(0, 0), directionResult.get(1, 0), directionResult.get(2, 0));

    // move the camera
    origin = origin + direction;
    _screen.move(direction);
}

void raytracer::Camera::rotate(raytracer::Vector3D direction)
{
    _rotation = direction + _rotation;
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

    // get the center of the rectangle
    Point3D center = _screen.origin + _screen.bottom_side * 0.5 + _screen.left_side * 0.5;

    // get the vector between the camera origin and the center of the rectangle
    Vector3D originToCenter = center - origin;

    // rotate vectors around center
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

    Matrix bottomResult = rotationX * bottomMatrix;
    bottomResult = rotationY * bottomResult;
    bottomResult = rotationZ * bottomResult;

    Matrix leftResult = rotationX * leftMatrix;
    leftResult = rotationY * leftResult;
    leftResult = rotationZ * leftResult;

    _screen.bottom_side = Vector3D(bottomResult.get(0, 0), bottomResult.get(1, 0), bottomResult.get(2, 0));
    _screen.left_side = Vector3D(leftResult.get(0, 0), leftResult.get(1, 0), leftResult.get(2, 0));

    // rotate originToCenter vector
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
