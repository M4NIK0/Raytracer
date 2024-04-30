/*
** EPITECH PROJECT, 2024
** IObject.hpp
** File description:
** raytracer
*/

#pragma once

#include "../Math/Ray3D.hpp"
#include "../sfml/sfml.hpp"

namespace raytracer
{
    class IObject
    {
        public:
            virtual ~IObject() = default;

            virtual Point3D hit(const Ray3D &ray) = 0;

            virtual Vector3D getSurfaceNormal(const Point3D &point) = 0;
            virtual Vector3D getVolumeNormal(const Point3D &point) = 0;

            virtual Color getSurfaceAbsorbtion(const Point3D &point) = 0;
            virtual double getSurfaceRoughness(const Point3D &point) = 0;
            virtual double getSurfaceTransparency(const Point3D &point) = 0;

            virtual Color getVolumeAbsorbtion() = 0;
            virtual double getVolumeAbsorbtionCoeff() = 0;

            virtual void move(Vector3D vec) = 0;
            virtual void rotate(Vector3D vec) = 0;

            virtual bool getGlassState(const Point3D &point) = 0;

            virtual double getRefractionxionIndex() = 0;
            virtual double getReflexionIndex(const Point3D &point) = 0;

            virtual void setReflexionIndex(double index) = 0;
            virtual void setRefractionIndex(double index) = 0;
            virtual void setGlassState(bool state) = 0;
    };
}
