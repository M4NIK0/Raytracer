//
// Created by Eth22 on 4/15/24.
//

#ifndef RAYTRACER_SFML_HPP
#define RAYTRACER_SFML_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <valarray>
#include "../Render/Chunk.hpp"

#define FPS 60

namespace raytracer
{
    class Color {
        public:
            Color(double r, double g, double b) : r(r), g(g), b(b) {}

            double r;
            double g;
            double b;

            Color operator+(const Color& other) const {
                return {r + other.r, g + other.g, b + other.b};
            }

            Color operator*(const Color& other) const {
                return {r * other.r, g * other.g, b * other.b};
            }

            Color operator*(double scalar) const {
                return {r * scalar, g * scalar, b * scalar};
            }

            Color operator/(double scalar) const {
                return {r / scalar, g / scalar, b / scalar};
            }

            Color operator-(const Color& other) const {
                return {r - other.r, g - other.g, b - other.b};
            }

            Color operator+=(const Color& other) {
                r += other.r;
                g += other.g;
                b += other.b;
                return *this;
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
                r = (r / size);
                g = (g / size);
                b = (b / size);
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
        virtual void initImage(int width, int height) = 0;

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
        sfml();
        ~sfml() override = default;

        void initWindow(int width = 800, int height = 600) override;
        void endWindow() override;
        void drawCurrentchunkBoundaries(raytracer::Chunk chunk, size_t chunkSizeX, size_t chunkSizeY);
        void drawPixel(int x, int y, raytracer::Color color) override;
        void displayScreen() override;
        void clearWindow() override;
        int getEvent() override;
        void initImage(int width, int height) override;

    private:
        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<sf::Image> _image;
        std::unique_ptr<sf::Texture> _texture;
        std::unique_ptr<sf::Sprite> _sprite;
};

#endif //RAYTRACER_SFML_HPP
