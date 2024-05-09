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

void Parser::parseObjects() {
    libconfig::Setting& Objects = cfg->lookup("Objects");

    for(int i = 0; i < Objects.getLength(); ++i) {
        libconfig::Setting& object = Objects[i];

        std::string type = object["type"];
        if (type == "sphere") {
            raytracer::Sphere sphere;
            sphere.parseData(object);
        } // else if plugins objects
    }
}

void Parser::parseCamera() {
    libconfig::Setting& camera = cfg->lookup("camera");
    // Parse camera
    double fov = camera["fov"];
    double time_obturation = camera["time_obturation"];
    double sensitivity;
    if (camera.exists("sensitivity")) {
        sensitivity = camera["sensitivity"];
    } else {
        sensitivity = 100;
    }
    double position_x = camera["position_x"];
    double position_y = camera["position_y"];
    double position_z = camera["position_z"];
    double rotation_x = camera["rotation_x"];
    double rotation_y = camera["rotation_y"];
    double rotation_z = camera["rotation_z"];
}

void Parser::parseScreen() {
    libconfig::Setting& screen = cfg->lookup("screen");
    // Parse screen
}

void Parser::parseRenderer() {
    libconfig::Setting& renderer = cfg->lookup("renderer");
    // Parse renderer
    int nb_rays_diffusion = renderer["nb_rays_diffusion"];
    int nb_rays_reflection = renderer["nb_rays_reflection"];
    int nb_bounces = renderer["nb_bounces"];
    int render_size_x = renderer["render_size_x"];
    int render_size_y = renderer["render_size_y"];
    int nb_samples = renderer["nb_samples"];
    int chunk_size_x = renderer["chunk_size_x"];
    int chunk_size_y = renderer["chunk_size_y"];
}

void Parser::parseScene() {
    parseObjects();
    parseCamera();
    parseScreen();
    parseRenderer();
}