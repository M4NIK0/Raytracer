/*
** EPITECH PROJECT, 2024
** Cube.cpp
** File description:
** raytracer
*/

#include "Cube.hpp"

raytracer::Cube::~Cube() = default;

raytracer::Point3D raytracer::Cube::hit(const Ray3D &ray)
{
    // Convert the cube's rotation to a matrix
    raytracer::Matrix rotationMatrix;
    rotationMatrix = {
            {_rotation.x},
            {_rotation.y},
            {_rotation.z}
    };

    // Compute the inverse rotation matrix
    raytracer::Matrix inverseRotationMatrix = rotationMatrix.transpose();

    // Apply the inverse rotation to the ray's origin and direction
    Ray3D localRay;
    localRay.origin = matrixToVector(inverseRotationMatrix * vectorToMatrix(ray.origin - _position));
    localRay.direction = matrixToVector(inverseRotationMatrix * vectorToMatrix(ray.direction));

    double tmin = (_position.x - _sideLength / 2 - ray.origin.x) / ray.direction.x;
    double tmax = (_position.x + _sideLength / 2 - ray.origin.x) / ray.direction.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    double tymin = (_position.y - _sideLength / 2 - ray.origin.y) / ray.direction.y;
    double tymax = (_position.y + _sideLength / 2 - ray.origin.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return {INFINITY, INFINITY, INFINITY};
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    double tzmin = (_position.z - _sideLength / 2 - ray.origin.z) / ray.direction.z;
    double tzmax = (_position.z + _sideLength / 2 - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return {INFINITY, INFINITY, INFINITY};
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return ray.origin + ray.direction * tmin;
}

raytracer::Vector3D raytracer::Cube::getSurfaceNormal(const Point3D &point)
{
    return (point - _position);
}

raytracer::Vector3D raytracer::Cube::getVolumeNormal(const Point3D &point)
{
    return getSurfaceNormal(point);
}

raytracer::Color raytracer::Cube::getSurfaceAbsorbtion(const Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::Cube::getSurfaceRoughness(const Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::Cube::getSurfaceTransparency(const Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::Cube::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::Cube::getVolumeAbsorbtionCoeff()
{
    return _volumeAbsorbtionCoeff;
}

void raytracer::Cube::move(Vector3D vec)
{
    _position = _position + vec;
}

void raytracer::Cube::rotate(Vector3D vec)
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

    // Combine the rotation matrices
    raytracer::Matrix rotationMatrix = rotateZ * rotateY * rotateX;

    // Convert the cube's position to a matrix
    raytracer::Matrix positionMatrix;
    positionMatrix = {
            {_position.x},
            {_position.y},
            {_position.z}
    };

    // Apply the rotation matrix to the cube's position
    raytracer::Matrix rotatedPositionMatrix = rotationMatrix * positionMatrix;

    // Convert the result back to a Vector3D and update the cube's position
    _position.x = rotatedPositionMatrix.get(0, 0);
    _position.y = rotatedPositionMatrix.get(1, 0);
    _position.z = rotatedPositionMatrix.get(2, 0);
}

bool raytracer::Cube::getGlassState(const Point3D &point)
{
    return _isGlass;
}

double raytracer::Cube::getRefractionIndex()
{
    return _refractionIndex;
}

double raytracer::Cube::getReflexionIndex(const Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::Cube::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::Cube::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::Cube::setGlassState(bool state)
{
    _isGlass = state;
}

raytracer::Matrix raytracer::Cube::vectorToMatrix(raytracer::Vector3D vector3D)
{
    Matrix matrix(3, 1);
    matrix.set(0, 0, vector3D.x);
    matrix.set(1, 0, vector3D.y);
    matrix.set(2, 0, vector3D.z);
    return matrix;
}

raytracer::Vector3D raytracer::Cube::matrixToVector(raytracer::Matrix matrix)
{
    return Vector3D(matrix.get(0, 0), matrix.get(0, 1), matrix.get(0, 2));
}

raytracer::Color raytracer::Cube::getSurfaceEmission(const raytracer::Point3D &point)
{
    return _emissionColor;
}

double raytracer::Cube::getSurfaceEmissionIntensity(const raytracer::Point3D &point)
{
    return _emissionIntensity;
}

void raytracer::Cube::setSurfaceEmission(raytracer::Color color)
{
    _emissionColor = color;
}

void raytracer::Cube::setSurfaceEmissionIntensity(double intensity)
{
    _emissionIntensity = intensity;
}

void raytracer::Cube::setMotion(raytracer::Vector3D &translation, raytracer::Vector3D &rotation)
{
    _translation = translation;
    _rotation = rotation;
}

void raytracer::Cube::initiateMotion(double time, size_t steps)
{
    Vector3D totalTranslation = _translation * time;
    Vector3D totalRotation = _rotation * time;

    _translationStep = totalTranslation / steps;
    _rotationStep = totalRotation / steps;

    _position = _position - totalTranslation / 2;
    _rotation = _rotation - totalRotation / 2;
}

void raytracer::Cube::resetMotion()
{
    _position = _positionBackup;
    _rotation = {0, 0, 0};
}

void raytracer::Cube::stepMotion()
{
    _position = _position + _translationStep;
    _rotation = _rotation + _rotationStep;
}

raytracer::Point3D raytracer::Cube::getCenter() const
{
    return _position;
}

void raytracer::Cube::parseData(libconfig::Setting &config)
{

}
