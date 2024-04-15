//
// Created by Eth22 on 4/15/24.
//

#ifndef RAYTRACER_SFML_HPP
#define RAYTRACER_SFML_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include "../../include/display.hpp"

class SfmlData
{
    public:
        sf::RenderWindow* getWindow() { return _window; }
        void setWindow(sf::RenderWindow* window) { _window = window; }

    private:
    sf::RenderWindow* _window;
};

class sfml : public raytracer::IDisplay {
    public:
        ~sfml() override = default;

        void initWindow() override = 0;
        void endWindow() override = 0;
        void drawPixel(int x, int y, raytracer::Color color) override = 0;
        void clearWindow() override = 0;

    private:
        SfmlData _data;
        static void _initSfml(SfmlData& data, int width = 800, int height = 600);
        static void _endSfml(SfmlData& data);
        static void _clearScreen(SfmlData& data);
        static void _drawPixel(SfmlData& data, int x, int y, raytracer::Color color);

};


#endif //RAYTRACER_SFML_HPP
