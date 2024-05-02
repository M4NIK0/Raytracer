//
// Created by Eth22 on 4/30/24.
//

#include "Plane.hpp"

raytracer::Plane::~Plane() = default;

raytracer::Point3D raytracer::Plane::hit(const Ray3D &ray)
{
    double denominator = _normal.dot(ray.direction);
    if (std::abs(std::abs(denominator)) > 1e-6) {
        double t = (_position - ray.origin).dot(_normal) / denominator;
        if (t >= 0)
            return ray.origin + ray.direction * t;
    }
    return {INFINITY, INFINITY, INFINITY};
}

raytracer::Vector3D raytracer::Plane::getSurfaceNormal(const Point3D &point)
{
    return _normal;
}

raytracer::Vector3D raytracer::Plane::getVolumeNormal(const Point3D &point)
{
    return _normal;
}

raytracer::Color raytracer::Plane::getSurfaceAbsorbtion(const Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::Plane::getSurfaceRoughness(const Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::Plane::getSurfaceTransparency(const Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::Plane::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::Plane::getVolumeAbsorbtionCoeff()
{
    return _volumeAbsorbtionCoeff;
}

void raytracer::Plane::move(Vector3D vec)
{
    _position = _position + vec;
}

void raytracer::Plane::rotate(Vector3D vec)
{
    // Convert the rotation angles from degrees to radians
    double rx = vec.x * M_PI / 180.0;
    double ry = vec.y * M_PI / 180.0;
    double rz = vec.z * M_PI / 180.0;

    // Create rotation matrices for the x, y, and z axes
    raytracer::Matrix rotateX;
    rotateX = {
            {1, 0, 0},
            {0, cos(rx), -sin(rx)},
            {0, sin(rx), cos(rx)}
    };

    raytracer::Matrix rotateY;
    rotateY = {
            {cos(ry), 0, sin(ry)},
            {0, 1, 0},
            {-sin(ry), 0, cos(ry)}
    };

    raytracer::Matrix rotateZ;
    rotateZ = {
            {cos(rz), -sin(rz), 0},
            {sin(rz), cos(rz), 0},
            {0, 0, 1}
    };

    // Combine the rotation matrices in the opposite order
    raytracer::Matrix rotationMatrix = rotateX * rotateY * rotateZ;

    // Convert the plane's normal to a matrix
    raytracer::Matrix normalMatrix;
    normalMatrix = {
            {_normal.x},
            {_normal.y},
            {_normal.z}
    };

    // Apply the rotation matrix to the plane's normal
    raytracer::Matrix rotatedNormalMatrix = rotationMatrix * normalMatrix;

    // Convert the result back to a Vector3D and update the plane's normal
    _normal.x = rotatedNormalMatrix.get(0, 0);
    _normal.y = rotatedNormalMatrix.get(1, 0);
    _normal.z = rotatedNormalMatrix.get(2, 0);
}

bool raytracer::Plane::getGlassState(const Point3D &point)
{
    return _isGlass;
}

double raytracer::Plane::getRefractionxionIndex()
{
    return _refractionIndex;
}

double raytracer::Plane::getReflexionIndex(const Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::Plane::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::Plane::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::Plane::setGlassState(bool state)
{
    _isGlass = state;
}