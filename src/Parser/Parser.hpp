//
// Created by leo on 5/6/24.
//

#ifndef RAYTRACER_PARSER_H
#define RAYTRACER_PARSER_H

#include <libconfig.h++>
#include "../Render/Renderer.hpp"
#include "../Light/Objects/PointLight.hpp"
#include "../Objects/Primitives/Sphere.hpp"
#include "../Objects/Primitives/Plane.hpp"
#include "../Objects/Primitives/Triangle.hpp"
#include "../Objects/Advanced/WavefontObject.hpp"
#include "../Render/RenderProcessWrapper.hpp"
#include "../Factory/Factory.hpp"

class Parser{
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
        Parser();
        ~Parser();
        void parseConfig(const char* path);
        void parseObjects(raytracer::Renderer &renderer, std::vector<std::unique_ptr<raytracer::LibHandler>> &libs);
        void parseLights(raytracer::Renderer &renderer, std::vector<std::unique_ptr<raytracer::LibHandler>> &libs);
        void parseCamera(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper);
        void parseScene(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper, std::vector<std::unique_ptr<raytracer::LibHandler>> &libs);
    private:
        std::unique_ptr<libconfig::Config> cfg;
};


#endif //RAYTRACER_PARSER_H
