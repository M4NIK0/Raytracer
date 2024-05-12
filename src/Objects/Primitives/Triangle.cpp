#include "Triangle.hpp"

/*
** EPITECH PROJECT, 2024
** Triangle.cpp
** File description:
** raytracer
*/

raytracer::Triangle::Triangle(raytracer::Point3D a, raytracer::Point3D b, raytracer::Point3D c, Color surfaceAbsorbtion) : _a(a), _b(b), _c(c), _surfaceAbsorbtion(surfaceAbsorbtion)
{
    _aBackup = a;
    _bBackup = b;
    _cBackup = c;
}

raytracer::Triangle::Triangle() = default;

raytracer::Triangle::~Triangle() = default;

raytracer::Point3D raytracer::Triangle::hit(const Ray3D &ray)
{
    Vector3D edge1 = _b - _a;
    Vector3D edge2 = _c - _a;
    Vector3D h = ray.direction.cross(edge2);
    double a = edge1.dot(h);

    if (a > -0.00001 && a < 0.00001)
        return {INFINITY, INFINITY, INFINITY};
    double f = 1 / a;
    Vector3D s = ray.origin - _a;
    double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return {INFINITY, INFINITY, INFINITY};
    Vector3D q = s.cross(edge1);
    double v = f * ray.direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
        return {INFINITY, INFINITY, INFINITY};
    double t = f * edge2.dot(q);
    if (t > 0.00001)
        return ray.origin + ray.direction * t;
    return {INFINITY, INFINITY, INFINITY};
}

raytracer::Vector3D raytracer::Triangle::getSurfaceNormal(const raytracer::Point3D &point)
{
    Vector3D edge1 = _b - _a;
    Vector3D edge2 = _c - _a;
    return edge1.cross(edge2).normalize();
}

raytracer::Vector3D raytracer::Triangle::getVolumeNormal(const raytracer::Point3D &point)
{
    return getSurfaceNormal(point);
}

raytracer::Color raytracer::Triangle::getSurfaceAbsorbtion(const raytracer::Point3D &point)
{
    return _surfaceAbsorbtion;
}

double raytracer::Triangle::getSurfaceRoughness(const raytracer::Point3D &point)
{
    return _surfaceRoughness;
}

double raytracer::Triangle::getSurfaceTransparency(const raytracer::Point3D &point)
{
    return 0;
}

raytracer::Color raytracer::Triangle::getSurfaceEmission(const raytracer::Point3D &point)
{
    return _emissionColor;
}

double raytracer::Triangle::getSurfaceEmissionIntensity(const raytracer::Point3D &point)
{
    return _emissionIntensity;
}

raytracer::Color raytracer::Triangle::getVolumeAbsorbtion()
{
    return _volumeAbsorbtion;
}

double raytracer::Triangle::getVolumeAbsorbtionCoeff()
{
    return 0;
}

void raytracer::Triangle::move(raytracer::Vector3D vec)
{
    _a = _a + vec;
    _b = _b + vec;
    _c = _c + vec;
}

void raytracer::Triangle::rotate(raytracer::Vector3D vec)
{
    Point3D center = getCenter();

    _a = Point3D::rotateAroundCenter(_a, center, vec.x, vec.y, vec.z);
    _b = Point3D::rotateAroundCenter(_b, center, vec.x, vec.y, vec.z);
    _c = Point3D::rotateAroundCenter(_c, center, vec.x, vec.y, vec.z);
}

bool raytracer::Triangle::getGlassState(const raytracer::Point3D &point)
{
    return _glassState;
}

double raytracer::Triangle::getRefractionIndex()
{
    return _refractionIndex;
}

double raytracer::Triangle::getReflexionIndex(const raytracer::Point3D &point)
{
    return _reflexionIndex;
}

void raytracer::Triangle::setReflexionIndex(double index)
{
    _reflexionIndex = index;
}

void raytracer::Triangle::setRefractionIndex(double index)
{
    _refractionIndex = index;
}

void raytracer::Triangle::setGlassState(bool state)
{
    _glassState = state;
}

void raytracer::Triangle::setSurfaceEmission(raytracer::Color color)
{
    _emissionColor = color;
}

void raytracer::Triangle::setSurfaceEmissionIntensity(double intensity)
{
    _emissionIntensity = intensity;
}

void raytracer::Triangle::setMotion(raytracer::Vector3D &translation, raytracer::Vector3D &rotation)
{
    _translation = translation;
    _rotation = rotation;
}

void raytracer::Triangle::initiateMotion(double time, size_t steps)
{
    Vector3D totalTranslation = _translation * time;
    Vector3D totalRotation = _rotation * time;

    _translationStep = totalTranslation / steps;
    _rotationStep = totalRotation / steps;

    move(Vector3D()-(totalTranslation / 2));
    rotate(Vector3D()-(totalRotation / 2));
}

void raytracer::Triangle::resetMotion()
{

}

void raytracer::Triangle::stepMotion()
{
    move(_translationStep);
    rotate(_rotationStep);
}

raytracer::Point3D raytracer::Triangle::getCenter() const
{
    Point3D center;
    center.x = (_a.x + _b.x + _c.x) / 3;
    center.y = (_a.y + _b.y + _c.y) / 3;
    center.z = (_a.z + _b.z + _c.z) / 3;

    return center;
}

void raytracer::Triangle::parseData(libconfig::Setting &config)
{
try {
        libconfig::Setting &a = config["a"];
        _a = raytracer::Point3D(a["x"], a["y"], a["z"]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("a not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("a need to be an array of double");
    }

    try {
        libconfig::Setting &b = config["b"];
        _b = raytracer::Point3D(b["x"], b["y"], b["z"]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("b not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("b need to be an array of double");
    }

    try {
        libconfig::Setting &c = config["c"];
        _c = raytracer::Point3D(c["x"], c["y"], c["z"]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("c not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("c need to be an array of double");
    }

    try {
        libconfig::Setting& translation = config["translationSpeed"];
        _translation = Vector3D(translation[0], translation[1], translation[2]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("translationSpeed is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("translationSpeed must be a vector of double");
    }

    try {
        libconfig::Setting& translation = config["rotationSpeed"];
        _translation = Vector3D(translation[0], translation[1], translation[2]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("rotationSpeed is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("rotationSpeed must be a vector of double");
    }

    try {
        libconfig::Setting& color = config["color"];
        _surfaceAbsorbtion.r = ((double)color[0]) / 255.0;
        _surfaceAbsorbtion.g = ((double)color[1]) / 255.0;
        _surfaceAbsorbtion.b = ((double)color[2]) / 255.0;
        if (_surfaceAbsorbtion.r < 0 || _surfaceAbsorbtion.r > 1 || _surfaceAbsorbtion.g < 0 || _surfaceAbsorbtion.g > 1 || _surfaceAbsorbtion.b < 0 || _surfaceAbsorbtion.b > 1)
            throw Error("color must be between 0 & 255");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("color is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("color must be a vector of double");
    }

    try {
        _emissionIntensity = config["emissionIntensity"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("emissionIntensity not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("emissionIntensity must be a double");
    }

    try {
        _emissionColor = {config["emissionColor"][0], config["emissionColor"][1], config["emissionColor"][2]};
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("emissionColor not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("emissionColor must be an array of 3 double");
    }

    try {
        _reflexionIndex = config["reflexion"];
        if (_reflexionIndex < 0 || _reflexionIndex > 1)
            throw Error("reflexion must be between 0 and 1");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Error("reflexion is missing");
    } catch (libconfig::SettingTypeException &e) {
        throw Error("reflexion must be a double");
    }
}
