/*
** EPITECH PROJECT, 2024
** Cube.hpp
** File description:
** raytracer
*/

#pragma once
#include "../IObject.hpp"
#include "../../Math/Matrix.hpp"

namespace raytracer
{
    class Cube : public IObject
    {
    public:
        Cube(raytracer::Point3D pos, double r, Color surfaceReflexion) : _sideLength(r), _position(pos), _surfaceAbsorbtion(surfaceReflexion), _volumeAbsorbtion(Color(0, 0, 0)), _emissionColor(Color(0, 0, 0)) {}
        ~Cube() override;

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

        void parseData(libconfig::Setting &config) override;

            Point3D getCenter() const override;

    private:
        double _sideLength;
        Point3D _position;
        Vector3D _rotation;

        double _surfaceRoughness = 0;
        Color _surfaceAbsorbtion;
        Color _volumeAbsorbtion;
        double _volumeAbsorbtionCoeff = 0;

        bool _isGlass = false;
        double _reflexionIndex = 0;
        double _refractionIndex = 1.5;

        raytracer::Matrix vectorToMatrix(Vector3D vector3D);

        Vector3D matrixToVector(Matrix matrix);

        Color _emissionColor;
        double _emissionIntensity = 0;

        Vector3D _translation = {0, 0, 0};

        Vector3D _translationStep = {0, 0, 0};

        Matrix _rotationMatrix = Matrix(3, 3);

        Vector3D _rotationStep = {0, 0, 0};

        Matrix _translationMatrix = Matrix(3, 1);

        Matrix _rotationMatrixX = Matrix(3, 3);

        Matrix _rotationMatrixY = Matrix(3, 3);

        Matrix _rotationMatrixZ = Matrix(3, 3);

        Matrix _rotationMatrixXStep = Matrix(3, 3);

        Matrix _rotationMatrixYStep = Matrix(3, 3);

        Matrix _rotationMatrixZStep = Matrix(3, 3);

        Matrix _rotationMatrixStep = Matrix(3, 3);

        Matrix _rotationMatrixStepBackup = Matrix(3, 3);

        Matrix _rotationMatrixBackup = Matrix(3, 3);

        Matrix _rotationMatrixXBackup = Matrix(3, 3);

        Matrix _rotationMatrixYBackup = Matrix(3, 3);

        Vector3D _positionBackup = {0, 0, 0};


    };
}