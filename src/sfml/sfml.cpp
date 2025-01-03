//
// Created by Eth22 on 4/15/24.
//

#include <iostream>
#include "sfml.hpp"

sfml::sfml()
{
    if (std::getenv("DISPLAY") != nullptr)
    {
        _image = std::make_unique<sf::Image>();
        _texture = std::make_unique<sf::Texture>();
        _sprite = std::make_unique<sf::Sprite>();
    }
    else
    {
        throw IDisplayError("No display detected");
    }
}

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
    _image->setPixel(x, y, sf::Color(color.r, color.g, color.b));
}

void sfml::displayScreen()
{
    _texture->loadFromImage(*_image);

    *_sprite = sf::Sprite();
    _sprite->setTexture(*_texture);

    _sprite->setScale(_window->getSize().x / (_image->getSize().x * 1.0f), _window->getSize().y / (_image->getSize().y * 1.0f));

    _window->setTitle("Blender 4.1 - " + std::to_string(_image->getSize().x) + "x" + std::to_string(_image->getSize().y));

    _window->draw(*_sprite);
    _window->display();
}

void sfml::clearWindow()
{
    _image->create(_image->getSize().x, _image->getSize().y, sf::Color::Black);
    _window->clear();
}

int sfml::getEvent()
{
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        return 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        return 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return 7;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        return 6;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        return 8;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        return 9;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return 10;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return 11;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return 12;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        return 13;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return 14;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return 15;
    return 0;
}

void sfml::initImage(int width, int height)
{
    _image->create(width, height, sf::Color::Black);
}

void sfml::drawCurrentchunkBoundaries(raytracer::Chunk chunk, size_t chunkSizeX, size_t chunkSizeY)
{
    for (size_t x = 0; x < chunk.width; x++)
    {
        for (size_t y = 0; y < chunk.height; y++)
        {
            if (x == 0 || y == 0 || x == chunk.width - 1 || y == chunk.height - 1)
                drawPixel(x + (chunkSizeX * chunk.x), y + (chunkSizeY * chunk.y), raytracer::Color(255, 255, 255));
        }
    }
}
