/*
** EPITECH PROJECT, 2024
** DirectionalLight.hpp
** File description:
** dummyLight
*/

#pragma once

#include "../../../src/Light/ILight.hpp"

namespace raytracer
{
    class DirectionalLight : public ILight
    {
        public:
            class Error : public std::exception
            {
            public:
                Error(std::string const &message) noexcept
                        : _message(message) {}

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
            };
            DirectionalLight(): _color({255, 255, 255}), _intensity(1) {_color.normalize();}
            ~DirectionalLight();

            std::vector<Ray3D> getLightRays(const Point3D &hitPoint) override;

            Color getColor() override { return _color; }

            double getIntensity() override { return _intensity; }

            double getIntensityFromDistance(double distance) override { return _intensity; }

            Point3D getPosition() override { return {INFINITY, INFINITY, INFINITY}; }

            void setPosition(const Point3D &position) override {}

            void move(Vector3D vec) override {}

            void parseData(libconfig::Setting &config) override;

        private:
            Color _color;
            double _intensity;
            Vector3D _direction;
    };
}
