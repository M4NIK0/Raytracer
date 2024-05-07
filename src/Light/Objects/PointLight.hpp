/*
** EPITECH PROJECT, 2024
** PointLight.hpp
** File description:
** raytracer
*/

#pragma once

#include "../ILight.hpp"

namespace raytracer
{
    class PointLight : public ILight
    {
        public:
            PointLight(Color color, Point3D position, double intensity = 1) : _color(color), _position(position), _intensity(intensity) {_color.normalize();};
            ~PointLight();

            std::vector<Ray3D> getLightRays(const Point3D &hitPoint) override;

            Color getColor() override;

            double getIntensity() override;

            double getIntensityFromDistance(double distance) override;

            Point3D getPosition() override { return _position; }

            void setPosition(const Point3D &position) override { _position = position; }

            void move(Vector3D vec) override { _position = _position + vec; }

            void parseData(libconfig::Setting &config) override;

        private:
            Color _color;
            double _intensity;
            Point3D _position;
    };
}
