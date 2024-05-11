//
// Created by leo on 5/11/24.
//

#ifndef RAYTRACER_FACTORY_H
#define RAYTRACER_FACTORY_H

#include "../Objects/IObject.hpp"
#include "../Objects/Primitives/Sphere.hpp"
#include "../Objects/Primitives/Plane.hpp"
#include "../Objects/Primitives/Triangle.hpp"
#include "../Objects/Advanced/WavefontObject.hpp"
#include "../Light/ILight.hpp"
#include "../Light/Objects/PointLight.hpp"
#include <libconfig.h++>
#include <memory>

class Factory {
    public:
        Factory() = default;
        ~Factory() = default;

        static std::shared_ptr<raytracer::ILight> createLight(const std::string& type, libconfig::Setting& config);
        static std::shared_ptr<raytracer::IObject> createObject(const std::string& type, libconfig::Setting& config);
};


#endif //RAYTRACER_FACTORY_H
