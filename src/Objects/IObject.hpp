/*
** EPITECH PROJECT, 2024
** IObject.hpp
** File description:
** raytracer
*/

#pragma once

#include <libconfig.h++>
#include "../../include/Math/Ray3D.hpp"
#include "../Render/Color.hpp"

namespace raytracer
{
    class IObject
    {
        public:
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

            virtual ~IObject() = default;

            virtual Point3D hit(const Ray3D &ray) = 0;

            virtual Vector3D getSurfaceNormal(const Point3D &point) = 0;
            virtual Vector3D getVolumeNormal(const Point3D &point) = 0;

            virtual Color getSurfaceAbsorbtion(const Point3D &point) = 0;
            virtual double getSurfaceRoughness(const Point3D &point) = 0;
            virtual double getSurfaceTransparency(const Point3D &point) = 0;
            virtual Color getSurfaceEmission(const Point3D &point) = 0;
            virtual double getSurfaceEmissionIntensity(const Point3D &point) = 0;

            virtual Color getVolumeAbsorbtion() = 0;
            virtual double getVolumeAbsorbtionCoeff() = 0;

            virtual void move(Vector3D vec) = 0;
            virtual void rotate(Vector3D vec) = 0;

            virtual bool getGlassState(const Point3D &point) = 0;

            virtual double getRefractionIndex() = 0;
            virtual double getReflexionIndex(const Point3D &point) = 0;

            virtual void setReflexionIndex(double index) = 0;
            virtual void setRefractionIndex(double index) = 0;
            virtual void setGlassState(bool state) = 0;
            virtual void setSurfaceEmission(Color color) = 0;
            virtual void setSurfaceEmissionIntensity(double intensity) = 0;

            virtual void setMotion(Vector3D &translation, Vector3D &rotation) = 0;

            virtual void initiateMotion(double time, size_t steps) = 0;
            virtual void stepMotion() = 0;
            virtual void resetMotion() = 0;

            virtual Point3D getCenter() const = 0;

            virtual void parseData(libconfig::Setting &config) = 0;
    };
}
