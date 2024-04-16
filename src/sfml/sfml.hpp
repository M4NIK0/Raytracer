//
// Created by Eth22 on 4/15/24.
//

#ifndef RAYTRACER_SFML_HPP
#define RAYTRACER_SFML_HPP

#pragma once
#include <SFML/Graphics.hpp>

#define FPS 60

namespace raytracer
{
    class Color {
        public:
            Color(int r, int g, int b) : r(r), g(g), b(b) {}

            int r;
            int g;
            int b;
    };

    class IDisplay {
    public:
        virtual ~IDisplay() = default;

        virtual void initWindow() = 0;
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
