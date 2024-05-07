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
    cfg->readFile(path);
}

void Parser::parsePlane(libconfig::Setting &plane) {
    std::string axis = plane["axis"];
    double position = plane["position"];
    double scale = plane["scale"];
    double reflectivity = plane["reflectivity"];
    double roughness = plane["roughness"];
    libconfig::Setting& color = plane["color"];
    int r_color = color["r"];
    int g_color = color["g"];
    int b_color = color["b"];
    bool glass = plane["glass"];
    if (glass) {
        double refraction_index = plane["refraction_index"];
    }
}

void Parser::parseCube(libconfig::Setting &cube) {
    libconfig::Setting& position = cube["position"];
    double x = position[0];
    double y = position[1];
    double z = position[2];
    double size = cube["size"];
    double scale = cube["scale"];
    double reflectivity = cube["reflectivity"];
    double roughness = cube["roughness"];
    libconfig::Setting& color = cube["color"];
    int r_color = color["r"];
    int g_color = color["g"];
    int b_color = color["b"];
    bool glass = cube["glass"];
    if (glass) {
        double refraction_index = cube["refraction_index"];
    }
}

void Parser::parseCylinder(libconfig::Setting &cylinder) {
    libconfig::Setting& position = cylinder["position"];
    double x = position[0];
    double y = position[1];
    double z = position[2];
    double radius = cylinder["radius"];
    double height = cylinder["height"];
    double scale = cylinder["scale"];
    double reflectivity = cylinder["reflectivity"];
    double roughness = cylinder["roughness"];
    libconfig::Setting& color = cylinder["color"];
    int r_color = color["r"];
    int g_color = color["g"];
    int b_color = color["b"];
    bool glass = cylinder["glass"];
    if (glass) {
        double refraction_index = cylinder["refraction_index"];
    }
}

void Parser::parseObjects() {
    libconfig::Setting& Objects = cfg->lookup("Objects");

    for(int i = 0; i < Objects.getLength(); ++i) {
        libconfig::Setting& object = Objects[i];

        std::string type = object["type"];
        if (type == "sphere") {
            parseSphere(object);
        }
        else if (type == "plane") {
            parsePlane(object);
        } else if (type == "cube") {
            parseCube(object);
        } else if (type == "cylinder") {
            parseCylinder(object);
        }
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