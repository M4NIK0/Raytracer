//
// Created by Eth22 on 4/15/24.
//

#include "sfml.hpp"

void sfml::initWindow(int width, int height)
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Blender 4.1", sf::Style::Titlebar | sf::Style::Close);
    _window->setFramerateLimit(FPS);
    _image.create(width, height, sf::Color::Black);
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
    _sprite.setTexture(_texture);
    //resize sprite to fill window using image
    _sprite.setScale(_window->getSize().x / _image.getSize().x, _window->getSize().y / _image.getSize().y);
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
