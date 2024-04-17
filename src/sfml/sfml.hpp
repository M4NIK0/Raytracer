//
// Created by Eth22 on 4/15/24.
//

#ifndef RAYTRACER_SFML_HPP
#define RAYTRACER_SFML_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <valarray>

#define FPS 60

namespace raytracer
{
    class Color {
        public:
            Color(int r, int g, int b) : r(r), g(g), b(b) {}

            int r;
            int g;
            int b;

            Color operator+(const Color& other) {
                return Color(r + other.r, g + other.g, b + other.b);
            }

            Color operator*(const Color& other) {
                return Color(r * other.r, g * other.g, b * other.b);
            }

            Color operator*(double scalar) {
                return Color(r * scalar, g * scalar, b * scalar);
            }

            void cap() {
                r = r > 255 ? 255 : r;
                g = g > 255 ? 255 : g;
                b = b > 255 ? 255 : b;

                r = r < 0 ? 0 : r;
                g = g < 0 ? 0 : g;
                b = b < 0 ? 0 : b;
            }

            void normalize()
            {
                double size = sqrt(r * r + g * g + b * b);
                (r /= size) * 255;
                (g /= size) * 255;
                (b /= size) * 255;
            }
    };

    class IDisplay {
    public:
        virtual ~IDisplay() = default;

        virtual void initWindow(int width, int height) = 0;
        virtual void endWindow() = 0;
        virtual void drawPixel(int x, int y, Color color) = 0;
        virtual void displayScreen() = 0;
        virtual void clearWindow() = 0;
        virtual int getEvent() = 0;

        class IDisplayError : public std::exception {
        public:
            explicit IDisplayError(const std::string& message) : _message(message) {}

            const char* what() const noexcept override {
                return _message.c_str();
            }

        private:
            std::string _message;
        };
    };
}

class sfml : public raytracer::IDisplay {
    public:
        ~sfml() override = default;

        void initWindow(int width = 800, int height = 600) override;
        void endWindow() override;
        void drawPixel(int x, int y, raytracer::Color color) override;
        void displayScreen() override;
        void clearWindow() override;
        int getEvent() override;

    private:
        std::unique_ptr<sf::RenderWindow> _window;
        sf::Image _image;
        sf::Texture _texture;
        sf::Sprite _sprite;
};

#endif //RAYTRACER_SFML_HPP
