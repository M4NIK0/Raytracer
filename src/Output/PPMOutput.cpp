/*
** EPITECH PROJECT, 2024
** PPMOutput.cpp
** File description:
** raytracer
*/

#include "PPMOutput.hpp"

void raytracer::PPMOutput::createFile(const std::string &filename, int width, int height)
{
    _filename = filename;
    _width = width;
    _height = height;
}

void raytracer::PPMOutput::writeToFile()
{
    std::ofstream file(_filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << _filename << std::endl;
        return;
    }

    writeHeader(file);
    writePixels(file);

    if (file.fail())
    {
        std::cerr << "Error: Failed to write to file " << _filename << std::endl;
        return;
    }

    std::cout << "File " << _filename << " written successfully." << std::endl;
}

void raytracer::PPMOutput::writePixels(std::ofstream &file)
{
    for (const auto& pixel : _pixels)
    {
        file << static_cast<char>(pixel.r)
             << static_cast<char>(pixel.g)
             << static_cast<char>(pixel.b);
    }
}

void raytracer::PPMOutput::writeHeader(std::ofstream &file) const
{
    file << "P6\n" << _width << " " << _height << "\n255\n";
}
