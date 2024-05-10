/*
** EPITECH PROJECT, 2024
** WavefontObject.hpp
** File description:
** raytracer
*/

#pragma once

#include "../IObject.hpp"
#include "../Primitives/Triangle.hpp"
#include "../Primitives/Sphere.hpp"
#include "../../Render/RenderPoint.hpp"
#include "../../Math/Matrix.hpp"

namespace raytracer
{
    class WavefontObject : public IObject
    {
        public:
            WavefontObject();
            WavefontObject(const std::string &path, const Point3D& position, Color surfaceAbsorbtion);
            ~WavefontObject() override;

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

        private:
            std::vector<std::shared_ptr<IObject>> _triangles = {};
            Sphere _boundingSphere;

            Point3D _position;
            Point3D _positionBackup;

            double _surfaceRoughness = 1;
            Color _surfaceAbsorbtion;
            Color _volumeAbsorbtion;
            double _volumeAbsorbtionCoeff = 0;

            double _refractionIndex = 1;
            double _reflexionIndex = 0;
            bool _isGlass = false;

            Color _emissionColor;
            double _emissionIntensity = 0;

            Vector3D _translation = {0, 0, 0};
            Vector3D _rotation = {0, 0, 0};

            Vector3D _translationStep = {0, 0, 0};
            Vector3D _rotationStep = {0, 0, 0};

            void _loadWavefont(const std::string &path);
            void _createBoundingSphere(std::vector<Point3D> &points);

            static Point3D _getPointFromLine(const std::string &line);
            static Triangle _createTriangleFromLine(const std::string &line, const std::vector<Point3D> &points);
    };
}
