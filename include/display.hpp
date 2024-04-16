//
// Created by Eth22 on 4/15/24.
//

#ifndef RAYTRACER_DISPLAY_HPP
#define RAYTRACER_DISPLAY_HPP

#pragma once
#include <exception>
#include <string>
#include <utility>

namespace raytracer
{
    class Color {
        public:
            explicit Color(short r = 0, short g = 0, short b = 0) : r(r), g(g), b(b) {}

            short r, g, b;
    };

    class IDisplay {
        public:
            virtual ~IDisplay() = default;

            class IDisplayError : public std::exception
            {
                public:
                    IDisplayError(std::string message) : _message(std::move(message)) {}
                    const char* what() const noexcept override { return _message.c_str(); }

                private:
                    std::string _message;
            };

            virtual void initWindow() = 0;
            virtual void endWindow() = 0;
            virtual void drawPixel(int x, int y, Color color) = 0;
            virtual void displayScreen() = 0;
            virtual void clearWindow() = 0;
            virtual int getEvent() = 0;
    };
}

#endif //RAYTRACER_DISPLAY_HPP
