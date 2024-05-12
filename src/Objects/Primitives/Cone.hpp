/*
** EPITECH PROJECT, 2024
** Cone.hpp
** File description:
** raytracer
*/

#pragma once

#include "../IObject.hpp"
#include <libconfig.h++>

namespace raytracer
{
    class Cone : public IObject
    {
    public:
    public:
        Cone();
        Cone(raytracer::Point3D apex, double height, double baseRadius, Color surfaceReflexion)
                : _height(height), _baseRadius(baseRadius), _apex(apex),
                  _positionBackup(apex), _surfaceAbsorbtion(surfaceReflexion), _volumeAbsorbtion(Color(0, 0, 0)), _emissionColor(Color(0, 0, 0)) {};

        class Error : public std::exception
        {
        public:
            Error(std::string const &message) :
                    _message(message) {};

            const char *what() const noexcept override
            {
                return _message.c_str();
            }

        private:
            std::string _message;
        };

        ~Cone();

        Point3D hit(const Ray3D &ray) override;

        Vector3D getSurfaceNormal(const Point3D &point) override;
        Vector3D getVolumeNormal(const Point3D &point) override;

        Color getSurfaceAbsorbtion(const Point3D &point) override;
        double getSurfaceRoughness(const Point3D &point) override;
        double getSurfaceTransparency(const Point3D &point) override;
        Color getSurfaceEmission(const Point3D &point) override;
        double getSurfaceEmissionIntensity(const Point3D &point) override;

        Color getVolumeAbsorbtion() override;
        double getVolumeAbsorbtionCoeff() override;

        void move(Vector3D vec) override;
        void rotate(Vector3D vec) override;

        bool getGlassState(const Point3D &point) override;

        double getRefractionIndex() override;
        double getReflexionIndex(const Point3D &point) override;

        void setReflexionIndex(double index) override;
        void setRefractionIndex(double index) override;
        void setGlassState(bool state) override;
        void setSurfaceEmission(Color color) override;
        void setSurfaceEmissionIntensity(double intensity) override;

        void setMotion(Vector3D &translation, Vector3D &rotation) override;
        void initiateMotion(double time, size_t steps) override;
        void resetMotion() override;

        void stepMotion() override;

        Point3D getCenter() const override;
        void parseData(libconfig::Setting &config) override;

    private:
        double _height;
        double _baseRadius;
        Point3D _apex;
        Point3D _position;
        Point3D _positionBackup;

        double _surfaceRoughness = 1;
        Color _surfaceAbsorbtion;
        Color _volumeAbsorbtion;
        double _volumeAbsorbtionCoeff = 0;
        Color _emissionColor;
        double _emissionIntensity = 0;

        bool _isGlass = false;
        double _reflexionIndex = 0;
        double _refractionIndex = 1.5;

        Vector3D _translation = {0, 0, 0};
        Vector3D _rotation = {0, 0, 0};

        Vector3D _translationStep = {0, 0, 0};
        Vector3D _rotationStep = {0, 0, 0};
    };
}
