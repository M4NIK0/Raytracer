//
// Created by Eth22 on 4/15/24.
//

#include <iostream>
#include "sfml.hpp"

void sfml::initWindow(int width, int height)
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Blender 4.1", sf::Style::Titlebar | sf::Style::Close);
    _window->setFramerateLimit(FPS);
}

void sfml::endWindow()
{
    _window->close();
}

void sfml::drawPixel(int x, int y, raytracer::Color color)
{
    _image.setPixel(x, y, sf::Color(color.r, color.g, color.b));
}

void sfml::displayScreen()
{
    _texture.loadFromImage(_image);

    _sprite = sf::Sprite();
    _sprite.setTexture(_texture);

    _sprite.setScale(_window->getSize().x / (_image.getSize().x * 1.0f), _window->getSize().y / (_image.getSize().y * 1.0f));

    _window->draw(_sprite);
    _window->display();
}

void sfml::clearWindow()
{
    _image.create(_image.getSize().x, _image.getSize().y, sf::Color::Black);
    _window->clear();
}

int sfml::getEvent()
{
    sf::Event event;
    while (_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            return 1;
    }
    return 0;
}

void sfml::initImage(int width, int height)
{
    _image.create(width, height, sf::Color::Black);
}
