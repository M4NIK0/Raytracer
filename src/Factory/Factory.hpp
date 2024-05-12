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
#include "../LibHandler/LibHandler.hpp"
#include <libconfig.h++>
#include <memory>

namespace raytracer
{
    class Factory {
        public:
            class Error : public std::exception {
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
            Factory() = default;
            ~Factory() = default;

            static std::shared_ptr<raytracer::ILight> createLight(const std::string& type, libconfig::Setting& config, std::vector<raytracer::LibHandler> &libs);
            static std::shared_ptr<raytracer::IObject> createObject(const std::string& type, libconfig::Setting& config, std::vector<raytracer::LibHandler> &libs);
        };
}


#endif //RAYTRACER_FACTORY_H
