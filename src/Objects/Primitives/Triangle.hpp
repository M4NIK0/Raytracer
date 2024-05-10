/*
** EPITECH PROJECT, 2024
** Triangle.hpp
** File description:
** raytracer
*/

#pragma once

#include "../IObject.hpp"

namespace raytracer
{
    class Triangle: public IObject
    {
        public:
            Triangle();
            Triangle(Point3D a, Point3D b, Point3D c, Color surfaceAbsorbtion);

            ~Triangle() override;

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
            Point3D _a;
            Point3D _b;
            Point3D _c;

            Point3D _aBackup;
            Point3D _bBackup;
            Point3D _cBackup;

            Vector3D _normal;
            double _surfaceRoughness = 1;

            Color _surfaceAbsorbtion;
            Color _volumeAbsorbtion;
            double _volumeAbsorbtionCoeff = 0;
            Color _emissionColor;
            double _emissionIntensity = 0;

            bool _glassState = false;
            double _refractionIndex = 1;
            double _reflexionIndex = 0;

            Vector3D _translation = {0, 0, 0};
            Vector3D _rotation = {0, 0, 0};

            Vector3D _translationStep = {0, 0, 0};
            Vector3D _rotationStep = {0, 0, 0};
    };
}
