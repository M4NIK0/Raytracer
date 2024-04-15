//
// Created by Eth22 on 4/15/24.
//

#ifndef RAYTRACER_SFML_HPP
#define RAYTRACER_SFML_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include "../../include/display.hpp"

#define FPS 60

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

        void initWindow() override;
        void endWindow() override;
        void drawPixel(int x, int y, raytracer::Color color) override;
        void displayScreen() override;
        void clearWindow() override;
        int getEvent() override;

    private:
        SfmlData _data;

        static void _initSfml(SfmlData& data, int width = 800, int height = 600);
        static void _endSfml(SfmlData& data);
        static void _clearScreen(SfmlData& data);
        static void _drawPixel(SfmlData& data, int x, int y, raytracer::Color color);
        static void _updateScreen(SfmlData& data);
        static int _awaitInput(SfmlData& data);

};

#endif //RAYTRACER_SFML_HPP
