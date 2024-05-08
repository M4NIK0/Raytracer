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

bool isFileWritable(const std::string& filename)
{
    std::filesystem::path p(filename);
    if (!std::filesystem::exists(p))
    {
        std::cerr << "Error: File " << filename << " does not exist." << std::endl;
        return false;
    }

    std::ofstream file(filename, std::ios::app);
    bool writable = file.good();
    file.close();

    return writable;
}

void raytracer::PPMOutput::writeToFile()
{
    if (!isFileWritable(_filename))
    {
        createFile(_filename, _width, _height);
    }

    std::ofstream file(_filename, std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << _filename << std::endl;
        return;
    }

    writeHeader(file);
    writePixels(file);

    file.close();

    if (file.fail())
    {
        std::cerr << "Error: Failed to write to file " << _filename << std::endl;
        return;
    }

    std::cout << "File successfully written at : " << std::filesystem::current_path() << _filename << std::endl;
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
