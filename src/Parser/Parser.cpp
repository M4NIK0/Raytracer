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
    libconfig::Setting& Objects = cfg->lookup("Objects");

    for(int i = 0; i < Objects.getLength(); ++i) {
        libconfig::Setting& object = Objects[i];

        std::string type = object["type"];
        if (type == "sphere") {
            raytracer::Sphere sphere;
            sphere.parseData(object);
            renderer.addObject(std::make_shared<raytracer::Sphere>(sphere));
        } // else if plugins objects
    }
}

raytracer::Camera Parser::parseCamera() {
    libconfig::Setting& camera = cfg->lookup("camera");

    try {
        raytracer::Camera tmp(camera["width"], camera["height"]);
        return tmp;
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("Camera width or height not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("Camera width or height must be an integer");
    }
}

raytracer::Renderer Parser::parseRenderer() {
    libconfig::Setting& renderer = cfg->lookup("renderer");
    raytracer::Camera camera = parseCamera();

    raytracer::Renderer render(camera);
    try {
        render.renderData.diffuseRays = renderer["diffusion"];
        if (render.renderData.diffuseRays > 2048)
            throw Parser::Error("diffusion must be between 0 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("diffusion not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("diffusion must be an int");
    }

    try {
        render.renderData.maxBounces = renderer["bounces"];
        if (render.renderData.maxBounces > 2048)
            throw Parser::Error("bounces must be between 0 and 2048");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("bounces not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("bounces must be an int");
    }

    try {
        render.renderData.reflexionsRays = renderer["reflexions"];
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

    try {
        render.renderData.width = renderer["width"];
        if (render.renderData.width < 1)
            throw Parser::Error("width must be greater than 0");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("width not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("width must be an int");
    }

    try {
        render.renderData.height = renderer["height"];
        if (render.renderData.height < 1)
            throw Parser::Error("height must be greater than 0");
    } catch (libconfig::SettingNotFoundException &e) {
        throw Parser::Error("height not found");
    } catch (libconfig::SettingTypeException &e) {
        throw Parser::Error("height must be an int");
    }
    return render;
}

raytracer::Renderer Parser::parseScene() {
    raytracer::Renderer renderer = parseRenderer();
    parseObjects(renderer);
    return renderer;
}