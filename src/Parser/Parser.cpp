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
        }
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

raytracer::Camera Parser::parseCamera(int width, int height) {
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
    return tmp;
}

raytracer::Renderer Parser::parseRenderer(int width, int height) {
    if (!cfg->exists("Renderer"))
        throw Parser::Error("Renderer not found");
    libconfig::Setting& renderer = cfg->lookup("Renderer");
    raytracer::Camera camera = parseCamera(width, height);

    raytracer::Renderer render(camera);
    render.renderData.width = width;
    render.renderData.height = height;
    try {
        render.renderData.diffuseRays = renderer["diffusion"].TypeInt64;
        if (render.renderData.diffuseRays > 2048)
            throw Parser::Error("diffusion must be between 0 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("diffusion not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("diffusion must be an int");
    }

    try {
        render.renderData.maxBounces = renderer["bounces"].TypeInt64;
        if (render.renderData.maxBounces > 2048)
            throw Parser::Error("bounces must be between 0 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("bounces not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("bounces must be an int");
    }

    try {
        render.renderData.reflexionsRays = renderer["reflexions"].TypeInt64;
        if (render.renderData.reflexionsRays > 2048)
            throw Parser::Error("reflexions must be between 0 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("reflexions not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("reflexions must be an int");
    }

    try {
        render.renderData.chunkHeight = renderer["chunkHeight"];
        if (render.renderData.chunkHeight < 1 || render.renderData.chunkHeight > 2048)
            throw Parser::Error("chunkHeight must be between 1 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("chunkHeight not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("chunkHeight must be an int");
    }

    try {
        render.renderData.chunkWidth = renderer["chunkWidth"];
        if (render.renderData.chunkWidth < 1 || render.renderData.chunkWidth > 2048)
            throw Parser::Error("chunkWidth must be between 1 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("chunkWidth not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("chunkWidth must be an int");
    }

    try {
        render.renderData.maxSamples = renderer["samples"];
        if (render.renderData.maxSamples > 2048 || render.renderData.maxSamples < 1)
            throw Parser::Error("samples must be between 1 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("samples not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("samples must be an int");
    }
    return render;
}

raytracer::Renderer Parser::parseScene(int width, int height) {
    raytracer::Renderer renderer = parseRenderer(width, height);
    parseObjects(renderer);
    parseLights(renderer);
    return renderer;
}