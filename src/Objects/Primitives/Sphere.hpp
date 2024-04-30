/*
** EPITECH PROJECT, 2024
** Sphere.hpp
** File description:
** raytracer
*/

#pragma once

#include "../IObject.hpp"

namespace raytracer
{
    class Sphere : public IObject
    {
        public:
            Sphere(raytracer::Point3D pos, double r, Color &surfaceAbsorbtion) : _radius(r), _position(pos), _surfaceAbsorbtion(surfaceAbsorbtion), _volumeAbsorbtion(Color(0, 0, 0)) {}
            ~Sphere();

            Point3D hit(const Ray3D &ray) override;

            Vector3D getSurfaceNormal(const Point3D &point) override;
            Vector3D getVolumeNormal(const Point3D &point) override;

            Color getSurfaceAbsorbtion(const Point3D &point) override;
            double getSurfaceRoughness(const Point3D &point) override;
            double getSurfaceTransparency(const Point3D &point) override;

            Color getVolumeAbsorbtion() override;
            double getVolumeAbsorbtionCoeff() override;

            void move(Vector3D vec) override;
            void rotate(Vector3D vec) override;

            bool getGlassState(const Point3D &point) override;

            double getRefractionxionIndex() override;
            double getReflexionIndex(const Point3D &point) override;

            void setReflexionIndex(double index) override;
            void setRefractionIndex(double index) override;
            void setGlassState(bool state) override;

        private:
            double _radius;
            Point3D _position;

            double _surfaceRoughness = 0;
            Color _surfaceAbsorbtion;
            Color _volumeAbsorbtion;
            double _volumeAbsorbtionCoeff = 0;

            bool _isGlass = false;
            double _reflexionIndex = 0;
            double _refractionIndex = 1.5;
    };
}
