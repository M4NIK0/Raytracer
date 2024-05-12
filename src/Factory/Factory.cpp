//
// Created by leo on 5/11/24.
//

#include "Factory.hpp"

std::shared_ptr<raytracer::ILight> raytracer::Factory::createLight(const std::string& type, libconfig::Setting& config, std::vector<std::unique_ptr<raytracer::LibHandler>> &libs)
{
    if (type == "point") {
        std::shared_ptr<raytracer::PointLight> pointLight = std::make_shared<raytracer::PointLight>();
        pointLight->parseData(config);
        return pointLight;
    } else {
        std::string plugin = config["plugin"];
        try {
            plugin = std::string (config["plugin"]);
        } catch (std::exception &e) {
            throw Error("Cannot load plugin: " + std::string(e.what()));
        }
        std::string light = "getLight";
        libs.push_back(std::make_unique<raytracer::LibHandler>());
        std::unique_ptr<LibHandler> &libHandler = libs.back();

        libHandler->setPath(plugin);

        try {
            libHandler->openLib();
        } catch (std::exception &e)
        {
            libs.pop_back();
            throw Error("Cannot load plugin: " + std::string(e.what()));
        }

        std::shared_ptr<raytracer::ILight> obj;
        try {
            obj = libHandler->getObject<raytracer::ILight>(light);
        } catch (std::exception &e) {
            libs.pop_back();
            throw Error("Cannot load plugin: " + std::string(e.what()));
        }

        obj->parseData(config);
        return obj;
    }
}

std::shared_ptr<raytracer::IObject> raytracer::Factory::createObject(const std::string& type, libconfig::Setting& config, std::vector<std::unique_ptr<raytracer::LibHandler>> &libs)
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
        std::string plugin = config["plugin"];
        try {
            plugin = std::string (config["plugin"]);
        } catch (std::exception &e) {
            throw Error("Cannot load plugin: " + std::string(e.what()));
        }
        std::string object = "getObject";
        libs.push_back(std::make_unique<LibHandler>());
        std::unique_ptr<LibHandler> &libHandler = libs.back();

        libHandler->setPath(plugin);

        try {
            libHandler->openLib();
        } catch (std::exception &e)
        {
            libs.pop_back();
            throw Error("Cannot load plugin: " + std::string(e.what()));
        }

        std::shared_ptr<raytracer::IObject> obj;
        try {
            obj = libHandler->getObject<raytracer::IObject>(object);
        } catch (std::exception &e) {
            libs.pop_back();
            throw Error("Cannot load plugin: " + std::string(e.what()));
        }
        obj->parseData(config);
        return obj;
    }
}
