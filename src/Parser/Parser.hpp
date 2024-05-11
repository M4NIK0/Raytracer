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
        void parseObjects(raytracer::Renderer &renderer);
        void parseLights(raytracer::Renderer &renderer);
        void parseCamera(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper);
        void parseScene(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper);
        void parseRenderer(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper);
    private:
        libconfig::Config* cfg;
};


#endif //RAYTRACER_PARSER_H
