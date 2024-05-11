/*
** EPITECH PROJECT, 2024
** PPMOutput.hpp
** File description:
** raytracer
*/

#ifndef RAYTRACER_PPMOUTPUT_HPP
#define RAYTRACER_PPMOUTPUT_HPP

#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <filesystem>
#include "../Render/Color.hpp"

namespace raytracer
{
    class PPMOutput
    {
        public:
            PPMOutput(const std::string& filename, int width, int height) : _filename(filename), _width(width), _height(height) {}
            ~PPMOutput() = default;

            void createFile(const std::string &filename, int width, int height);

            void setPixel(int x, int y, const Color& color) { _pixels.push_back(color); }

            void writeToFile();
            void writePixels(std::ofstream &file);
            void writeHeader(std::ofstream &file) const;

        private:
            std::string _filename;
            int _width, _height;
            std::vector<raytracer::Color> _pixels;
    };
}

#endif //RAYTRACER_PPMOUTPUT_HPP
