//
// Created by Eth22 on 4/30/24.
//

#ifndef RAYTRACER_PLANE_HPP
#define RAYTRACER_PLANE_HPP

#include "../IObject.hpp"
#include "../../Math/Matrix.hpp"

namespace raytracer
{
    class Plane : public IObject
    {
    public:
        Plane(raytracer::Point3D pos, Vector3D normal, Color surfaceReflexion) : _normal(normal), _position(pos), _surfaceAbsorbtion(surfaceReflexion), _volumeAbsorbtion(Color(0, 0, 0)) {}
        ~Plane();

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
        Vector3D _normal;
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



#endif //RAYTRACER_PLANE_HPP
