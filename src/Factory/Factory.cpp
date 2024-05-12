//
// Created by leo on 5/11/24.
//

#include "Factory.hpp"

std::shared_ptr<raytracer::ILight> raytracer::Factory::createLight(const std::string& type, libconfig::Setting& config)
{
    if (type == "point") {
        std::shared_ptr<raytracer::PointLight> pointLight = std::make_shared<raytracer::PointLight>();
        pointLight->parseData(config);
        return pointLight;
    } else {
        try {
            std::string plugin = config["plugin"];
            std::string light = "getLight";
            raytracer::LibHandler libHandler(plugin);
            libHandler.openLib();
            libHandler.getObject<raytracer::ILight>(light);
            std::shared_ptr<raytracer::ILight> obj = libHandler.getObject<raytracer::ILight>(light);
            obj->parseData(config);
            std::cout << "Light created" << std::endl;
            return obj;
        } catch (std::exception &e) {
            throw Error("Cannot load plugin: " + std::string(e.what()));
        }
    }
}

std::shared_ptr<raytracer::IObject> raytracer::Factory::createObject(const std::string& type, libconfig::Setting& config)
{
    if (type == "sphere") {
        std::shared_ptr<raytracer::Sphere> sphere = std::make_shared<raytracer::Sphere>();
        sphere->parseData(config);
        return sphere;
    } else if (type == "plane") {
        std::shared_ptr<raytracer::Plane> plane = std::make_shared<raytracer::Plane>();
        plane->parseData(config);
        return plane;
    } else if (type == "triangle") {
        std::shared_ptr<raytracer::Triangle> triangle = std::make_shared<raytracer::Triangle>();
        triangle->parseData(config);
        return triangle;
    } else if (type == "OBJ") {
        std::shared_ptr<raytracer::WavefontObject> wavefontObject = std::make_shared<raytracer::WavefontObject>(config["path"]);
        wavefontObject->parseData(config);
        return wavefontObject;
    } else {
        try {
            std::string plugin = config["plugin"];
            std::string object = "Object";
            raytracer::LibHandler libHandler(plugin);
            libHandler.openLib();
            libHandler.getObject<raytracer::IObject>(object);
            std::shared_ptr<raytracer::IObject> obj = libHandler.getObject<raytracer::IObject>(object);
            obj->parseData(config);
            return obj;
        } catch (std::exception &e) {
            throw Error("Cannot load plugin: " + std::string(e.what()));
        }
    }
}