//
// Created by leo on 5/6/24.
//

#include "Parser.hpp"
#include <fstream>

Parser::Parser() {
    cfg = std::make_unique<libconfig::Config>();
}

Parser::~Parser() {}

void Parser::parseConfig(const char* path) {
    std::ifstream infile(path);
    if (!infile.good()) {
        throw Error("File does not exist: " + std::string(path));
    }

    try {
        cfg->readFile(path);
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file: " << path << std::endl;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
    }
}

void Parser::parseObjects(raytracer::Renderer &renderer, std::vector<std::unique_ptr<raytracer::LibHandler>> &libs) {
    if (!cfg->exists("Objects"))
        throw Parser::Error("Objects not found");
    libconfig::Setting& Objects = cfg->lookup("Objects");

    raytracer::Factory factory;

    for(int i = 0; i < Objects.getLength(); ++i) {
        libconfig::Setting& object = Objects[i];

        if (!object.exists("type"))
            throw Parser::Error("Object type not found");
        std::string type = object["type"];

        std::shared_ptr<raytracer::IObject> obj = raytracer::Factory::createObject(type, object, libs);
        if (obj != nullptr) {
            renderer.addObject(obj);
        }
    }
}

void Parser::parseLights(raytracer::Renderer &renderer, std::vector<std::unique_ptr<raytracer::LibHandler>> &libs)
{
    if (!cfg->exists("Lights"))
        throw Parser::Error("Lights not found");
    libconfig::Setting& Lights = cfg->lookup("Lights");

    for(int i = 0; i < Lights.getLength(); ++i) {
        libconfig::Setting& light = Lights[i];

        if (!light.exists("type"))
            throw Parser::Error("Light type not found");
        std::string type = light["type"];

        std::shared_ptr<raytracer::ILight> obj = raytracer::Factory::createLight(type, light, libs);
        if (obj != nullptr) {
            renderer.addLight(obj);
        }
    }
}

void Parser::parseCamera(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper) {
    if (!cfg->exists("Camera"))
        throw Parser::Error("Camera not found");
    libconfig::Setting& camera = cfg->lookup("Camera");

    double fov;
    try {
        fov = camera["fov"];
        if (fov <= 0 || fov >= 180)
            throw Parser::Error("fov must be between 0 and 180");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("fov not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("fov must be a double");
    }

    raytracer::Camera tmp(width, height, fov);
    try {
        tmp.origin = raytracer::Vector3D(camera["position"][0], camera["position"][1], camera["position"][2]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("position not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("position must be an array of 3 double");
    }
    try {
        tmp.exposure = camera["exposure"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("exposure not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("exposure must be a double");
    }
    try {
        tmp.sensitivity = camera["sensitivity"];
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("sensitivity not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("sensitivity must be a double");
    }

    raytracer::Vector3D rotation;
    try {
        rotation = raytracer::Vector3D(camera["rotation"][0], camera["rotation"][1], camera["rotation"][2]);
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("rotation not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("rotation must be an array of 3 double");
    }

    rendererWrapper.initCamera(tmp.sensitivity, tmp.exposure, tmp.origin, fov, rotation);
}

void Parser::parseScene(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper, std::vector<std::unique_ptr<raytracer::LibHandler>> &libs) {
    parseCamera(width, height, rendererWrapper);
    parseObjects(rendererWrapper.renderer, libs);
    parseLights(rendererWrapper.renderer, libs);
}