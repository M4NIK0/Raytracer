//
// Created by Eth22 on 4/15/24.
//

#include "sfml.hpp"

void sfml::_initSfml(SfmlData& data, int width, int height)
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Minecraft RTX");
    if (!window) {
        _endSfml(data);
        throw IDisplayError("Error creating window");
    }

    data.setWindow(window);
}

void sfml::_endSfml(SfmlData& data)
{
    if (data.getWindow()) {
        data.getWindow()->close();
    }

    data.setWindow(nullptr);
}

void sfml::_clearScreen(SfmlData& data)
{
    if (!data.getWindow()) {
        _endSfml(data);
        throw IDisplayError("Error clearing Window, no window found");
    }

    data.getWindow()->clear(sf::Color::Black);
}

void sfml::_drawPixel(SfmlData& data, int x, int y, raytracer::Color color)
{
    if (!data.getWindow()) {
        _endSfml(data);
        throw IDisplayError("Error drawing pixel, no window found");
    }

    sf::RectangleShape pixel(sf::Vector2f(1, 1));
    pixel.setPosition(x, y);
    pixel.setFillColor(sf::Color(color.r, color.g, color.b));
    data.getWindow()->draw(pixel);
}

void sfml::_updateScreen(SfmlData& data)
{
    if (!data.getWindow()) {
        _endSfml(data);
        throw IDisplayError("Error updating screen, no window found");
    }

    data.getWindow()->display();
}

int sfml::_awaitInput(SfmlData& data)
{
    if (!data.getWindow()) {
        _endSfml(data);
        throw IDisplayError("Error awaiting input, no window found");
    }

    sf::Event event;
    while (data.getWindow()->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            data.getWindow()->close();
            return 1;
        }
    }

    return 0;
}

void sfml::initWindow()
{
    _initSfml(_data, 800, 600);
}

void sfml::endWindow()
{
    _endSfml(_data);
}

void sfml::drawPixel(int x, int y, raytracer::Color color)
{
    _drawPixel(_data, x, y, color);
    displayScreen();
}

void sfml::displayScreen()
{
    _updateScreen(_data);
}

void sfml::clearWindow()
{
    _clearScreen(_data);
}

int sfml::getEvent()
{
    return _awaitInput(_data);
}
