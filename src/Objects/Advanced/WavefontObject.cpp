/*
** EPITECH PROJECT, 2024
** WavefontObject.cpp
** File description:
** raytracer
*/

#include "WavefontObject.hpp"
#include <fstream>

raytracer::WavefontObject::WavefontObject(const std::string &path, const Point3D& position, Color surfaceAbsorbtion)
{
    _loadWavefont(path);

    move(Vector3D(position.x, position.y, position.z));
    _boundingSphere.move(Vector3D(position.x, position.y, position.z));

    _surfaceAbsorbtion = surfaceAbsorbtion;
}

raytracer::WavefontObject::WavefontObject() = default;

raytracer::WavefontObject::~WavefontObject() = default;

raytracer::Point3D raytracer::WavefontObject::hit(const raytracer::Ray3D &ray)
{
    if (_triangles.empty())
        return {INFINITY, INFINITY, INFINITY};
    if (_boundingSphere.hit(ray) == Point3D(INFINITY, INFINITY, INFINITY))
        return {INFINITY, INFINITY, INFINITY};

    RenderPoint renderPoint;

    renderPoint.hitNearestObject(_triangles, const_cast<Ray3D &>(ray));

    if (renderPoint.distance == INFINITY)
        return {INFINITY, INFINITY, INFINITY};

    return renderPoint.hitPoint;
}

raytracer::Vector3D raytracer::WavefontObject::getSurfaceNormal(const raytracer::Point3D &point)
{
    std::shared_ptr<IObject> nearestTriangle = nullptr;
    double minimalDistance = INFINITY;

    // Find the nearest triangle
    for (auto &triangle : (_triangles)) {
        double distance = Point3D::distance(point, triangle->getCenter());
        if (distance < minimalDistance) {
            minimalDistance = distance;
            nearestTriangle = triangle;
        }
    }

    return nearestTriangle->getSurfaceNormal(point);
}

raytracer::Vector3D raytracer::WavefontObject::getVolumeNormal(const raytracer::Point3D &point)
{
    return getSurfaceNormal(point);
}

raytracer::Color raytracer::WavefontObject::getSurfaceAbsorbtion(const Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::WavefontObject::getSurfaceRoughness(const Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::WavefontObject::getSurfaceTransparency(const Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::WavefontObject::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::WavefontObject::getVolumeAbsorbtionCoeff()
{
    return _volumeAbsorbtionCoeff;
}

raytracer::Color raytracer::WavefontObject::getSurfaceEmission(const Point3D &point)
{
    return _emissionColor;
}

double raytracer::WavefontObject::getSurfaceEmissionIntensity(const Point3D &point)
{
    return _emissionIntensity;
}

void raytracer::WavefontObject::move(Vector3D vec)
{
    _position = _position + vec;
    _positionBackup = _position;

    for (auto &triangle : _triangles)
        triangle->move(vec);
}

void raytracer::WavefontObject::rotate(Vector3D vec)
{
}

bool raytracer::WavefontObject::getGlassState(const Point3D &point)
{
    return _isGlass;
}

double raytracer::WavefontObject::getRefractionIndex()
{
    return _refractionIndex;
}

double raytracer::WavefontObject::getReflexionIndex(const Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::WavefontObject::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::WavefontObject::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::WavefontObject::setGlassState(bool state)
{
    _isGlass = state;
}

void raytracer::WavefontObject::setSurfaceEmission(raytracer::Color color)
{
    _emissionColor = color;
}

void raytracer::WavefontObject::setSurfaceEmissionIntensity(double intensity)
{
    _emissionIntensity = intensity;
}

void raytracer::WavefontObject::setMotion(Vector3D &translation, Vector3D &rotation)
{
    _translation = translation;
    _rotation = rotation;
}

void raytracer::WavefontObject::initiateMotion(double time, size_t steps)
{
    Vector3D totalTranslation = _translation * time;
    Vector3D totalRotation = _rotation * time;

    _translationStep = totalTranslation / steps;
    _rotationStep = totalRotation / steps;

    _position = _position - totalTranslation / 2;
    _rotation = _rotation - totalRotation / 2;
}

void raytracer::WavefontObject::resetMotion()
{
    _position = _positionBackup;
}

void raytracer::WavefontObject::stepMotion()
{
    _position = _position + _translationStep;
    _rotation = _rotation + _rotationStep;
}

raytracer::Point3D raytracer::WavefontObject::getCenter() const
{
    return _position;
}

void raytracer::WavefontObject::_loadWavefont(const std::string &path)
{
    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + path);

    std::vector<Point3D> points;

    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);

        if (line[0] == 'v' && line[1] == ' ')
            points.push_back(_getPointFromLine(line));
        else if (line[0] == 'f' && line[1] == ' ')
            _triangles.push_back(std::make_shared<Triangle>(_createTriangleFromLine(line, points)));
    }

    _createBoundingSphere(points);
}

void raytracer::WavefontObject::_createBoundingSphere(std::vector<Point3D> &points)
{
    Point3D center;
    Point3D furthestPoint;

    for (auto &point : points)
    {
        center.x += point.x;
        center.y += point.y;
        center.z += point.z;
    }

    center.x /= points.size();
    center.y /= points.size();
    center.z /= points.size();

    for (auto &point : points)
    {
        if (Point3D::distance(center, point) > Point3D::distance(center, furthestPoint))
            furthestPoint = point;
    }

    _boundingSphere = Sphere(center, Point3D::distance(center, furthestPoint), Color());
}

raytracer::Point3D raytracer::WavefontObject::_getPointFromLine(const std::string &line)
{
    // format line stripping unnecessary characters
    std::string formattedLine = line;
    for (size_t i = 0; i < formattedLine.size(); i++)
    {
        if (formattedLine[i] == ' ' && formattedLine[i + 1] == ' ')
        {
            formattedLine.erase(i, 1);
            i--;
        }
    }
    formattedLine = formattedLine.substr(2);

    // split line into coordinates
    std::vector<std::string> coordinates;

    for (size_t i = 0; i < formattedLine.size(); i++)
    {
        if (formattedLine[i] == ' ')
        {
            coordinates.push_back(formattedLine.substr(0, i));
            formattedLine = formattedLine.substr(i + 1);
            i = 0;
        }
    }

    coordinates.push_back(formattedLine);

    return {std::stod(coordinates[0]), std::stod(coordinates[1]), std::stod(coordinates[2])};
}

raytracer::Triangle raytracer::WavefontObject::_createTriangleFromLine(const std::string &line, const std::vector<Point3D> &points)
{
    // format line stripping unnecessary characters
    std::string formattedLine = line;
    for (size_t i = 0; i < formattedLine.size(); i++)
    {
        if (formattedLine[i] == ' ' && formattedLine[i + 1] == ' ')
        {
            formattedLine.erase(i, 1);
            i--;
        }
    }
    formattedLine = formattedLine.substr(2);

    // split line into coordinates
    std::vector<std::string> coordinates;

    for (size_t i = 0; i < formattedLine.size(); i++)
    {
        if (formattedLine[i] == ' ')
        {
            coordinates.push_back(formattedLine.substr(0, i));
            formattedLine = formattedLine.substr(i + 1);
            i = 0;
        }
    }

    coordinates.push_back(formattedLine);

    return Triangle(points[std::stoi(coordinates[0]) - 1], points[std::stoi(coordinates[1]) - 1], points[std::stoi(coordinates[2]) - 1], Color());
}