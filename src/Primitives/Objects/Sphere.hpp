/*
** EPITECH PROJECT, 2024
** Sphere.hpp
** File description:
** raytracer
*/

#pragma once

#include "../IPrimitive.hpp"

namespace raytracer
{
    class Sphere : public IPrimitive
    {
        public:
            Sphere(raytracer::Point3D pos, double r, Color color) : radius(r), position(pos), color(color) {}
            ~Sphere();

            bool hits(const Ray3D &ray) override;
            Point3D hitPosition(const Ray3D &ray) override;
            Vector3D hitNormal(const Ray3D &ray) override;
            Vector3D getNormalFromPoint(const Point3D &point) override;
            Ray3D hitReflectedRay(const Ray3D &ray) override;
            void move(Vector3D vec) override;
            Color getColor() override { return color; }
            bool isGlass() override { return _isGlass; }
            void setColor(Color color) override { this->color = color; }
            double getReflexionIndice(const Ray3D &ray) override { return _reflexionIndex; }
            double getRefractionxionIndice(const Ray3D &ray) override { return _refractionIndex; }
            void setGlassState(bool state) override { _isGlass = state; }
            void setReflexionIndice(double indice) override { _reflexionIndex = indice; }
            void setRefractionIndice(double indice) override { _refractionIndex = indice; }

            double radius;
            Point3D position;
            Color color;
            bool _isGlass = false;
            double _reflexionIndex = 0.0;
            double _refractionIndex = 0.0;
    };
}
