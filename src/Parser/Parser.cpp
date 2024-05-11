//
// Created by leo on 5/6/24.
//

#include "Parser.hpp"

Parser::Parser() {
    cfg = new libconfig::Config();
}

Parser::~Parser() {
    delete cfg;
}

void Parser::parseConfig(const char* path) {
    try {
        cfg->readFile(path);
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file: " << path << std::endl;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
    }
}

void Parser::parseObjects(raytracer::Renderer &renderer) {
    if (!cfg->exists("Objects"))
        throw Parser::Error("Objects not found");
    libconfig::Setting& Objects = cfg->lookup("Objects");

    for(int i = 0; i < Objects.getLength(); ++i) {
        libconfig::Setting& object = Objects[i];

        if (!object.exists("type"))
            throw Parser::Error("Object type not found");
        std::string type = object["type"];
        if (type == "sphere") {
            std::shared_ptr<raytracer::Sphere> sphere = std::make_shared<raytracer::Sphere>();
            sphere->parseData(object);
            renderer.addObject(sphere);
        } else if (type == "plane") {
            raytracer::Plane plane;
            plane.parseData(object);
            renderer.addObject(std::make_shared<raytracer::Plane>(plane));
        } else if (type == "triangle") {
            raytracer::Triangle triangle;
            triangle.parseData(object);
            renderer.addObject(std::make_shared<raytracer::Triangle>(triangle));
        } else if (type == "OBJ") {
            if (!object.exists("path"))
                throw Parser::Error("path not found");
            raytracer::WavefontObject wavefontObject(object["path"]);
            wavefontObject.parseData(object);
            renderer.addObject(std::make_shared<raytracer::WavefontObject>(wavefontObject));
        }
    }
}

void Parser::parseLights(raytracer::Renderer &renderer)
{
    if (!cfg->exists("Lights"))
        throw Parser::Error("Lights not found");
    libconfig::Setting& Lights = cfg->lookup("Lights");

    for(int i = 0; i < Lights.getLength(); ++i) {
        libconfig::Setting& light = Lights[i];

        if (!light.exists("type"))
            throw Parser::Error("Light type not found");
        std::string type = light["type"];
        if (type == "point") {
            std::shared_ptr<raytracer::PointLight> pointLight = std::make_shared<raytracer::PointLight>();
            pointLight->parseData(light);
            renderer.addLight(pointLight);
        } // else if plugins lights
    }
}

void Parser::parseCamera(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper) {
    if (!cfg->exists("Camera"))
        throw Parser::Error("Camera not found");
    libconfig::Setting& camera = cfg->lookup("Camera");

    raytracer::Camera tmp(width, height);
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

    rendererWrapper.initCamera(tmp.sensitivity, tmp.exposure, tmp.origin, rotation);
}

void Parser::parseRenderer(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper) {
    if (!cfg->exists("Renderer"))
        throw Parser::Error("Renderer not found");
    libconfig::Setting& renderer = cfg->lookup("Renderer");
    parseCamera(width, height, rendererWrapper);

    rendererWrapper.renderer.renderData.width = width;
    rendererWrapper.renderer.renderData.height = height;
    try {
        rendererWrapper.renderer.renderData.diffuseRays = renderer["diffusion"].TypeInt64;
        if (rendererWrapper.renderer.renderData.diffuseRays > 2048)
            throw Parser::Error("diffusion must be between 0 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("diffusion not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("diffusion must be an int");
    }

    try {
        rendererWrapper.renderer.renderData.maxBounces = renderer["bounces"].TypeInt64;
        if (rendererWrapper.renderer.renderData.maxBounces > 2048)
            throw Parser::Error("bounces must be between 0 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("bounces not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("bounces must be an int");
    }

    try {
        rendererWrapper.renderer.renderData.reflexionsRays = renderer["reflexions"].TypeInt64;
        if (rendererWrapper.renderer.renderData.reflexionsRays > 2048)
            throw Parser::Error("reflexions must be between 0 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("reflexions not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("reflexions must be an int");
    }

    try {
        rendererWrapper.renderer.renderData.chunkHeight = renderer["chunkHeight"];
        if (rendererWrapper.renderer.renderData.chunkHeight < 1 || rendererWrapper.renderer.renderData.chunkHeight > 2048)
            throw Parser::Error("chunkHeight must be between 1 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("chunkHeight not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("chunkHeight must be an int");
    }

    try {
        rendererWrapper.renderer.renderData.chunkWidth = renderer["chunkWidth"];
        if (rendererWrapper.renderer.renderData.chunkWidth < 1 || rendererWrapper.renderer.renderData.chunkWidth > 2048)
            throw Parser::Error("chunkWidth must be between 1 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("chunkWidth not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("chunkWidth must be an int");
    }

    try {
        rendererWrapper.renderer.renderData.maxSamples = renderer["samples"];
        if (rendererWrapper.renderer.renderData.maxSamples > 2048 || rendererWrapper.renderer.renderData.maxSamples < 1)
            throw Parser::Error("samples must be between 1 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("samples not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("samples must be an int");
    }
}

void Parser::parseScene(int width, int height, raytracer::RenderProcessWrapper &rendererWrapper) {
    parseRenderer(width, height, rendererWrapper);
    parseObjects(rendererWrapper.renderer);
    parseLights(rendererWrapper.renderer);
}