//
// Created by leo on 5/11/24.
//

#include <string>
#include <iostream>
#include "ParseArg.hpp"


ParseArg::ParseArg(int ac, char **av) : _imageSize(800, 600), _chunkSize(16, 16), _threads(1), _samples(3), _bounces(2), _diffusionRays(1), _reflectionRays(1), _cli(false), _ne(false)
{
    if (ac < 3) {
        displayHelp(av[0]);
    }
    _configFile = av[1];
    _outputFile = av[2];
    for (int i = 3; i < ac; ++i) {
        std::string arg = av[i];
        if (arg == "-h") {
            displayHelp(av[0]);
        } else if (arg == "-is" && i + 2 < ac) {
            _imageSize = std::make_pair(std::stoi(av[++i]), std::stoi(av[++i]));
        } else if (arg == "-cs" && i + 2 < ac) {
            _chunkSize = std::make_pair(std::stoi(av[++i]), std::stoi(av[++i]));
        } else if (arg == "-t" && i + 1 < ac) {
            _threads = std::stoi(av[++i]);
        } else if (arg == "-s" && i + 1 < ac) {
            _samples = std::stoi(av[++i]);
        } else if (arg == "-b" && i + 1 < ac) {
            _bounces = std::stoi(av[++i]);
        } else if (arg == "-dr" && i + 1 < ac) {
            _diffusionRays = std::stoi(av[++i]);
        } else if (arg == "-rr" && i + 1 < ac) {
            _reflectionRays = std::stoi(av[++i]);
        } else if (arg == "-cli") {
            _cli = true;
        } else if (arg == "-ne") {
            _ne = true;
        } else {
            std::cerr << "Unrecognized argument: " << arg << std::endl;
        }
    }
}

void ParseArg::displayHelp(const std::string& name)
{
    std::cout << "Usage: " << name << " [config file] [output file] [options]" << std::endl;
    std::cout << "- `-h`: Display help" << std::endl;
    std::cout << "- `-is [image width] [image height]`: Set the image size, defaults to 800x600" << std::endl;
    std::cout << "- `-cs [chunk width] [chunk height]`: Set the chunk size, defaults to 16x16" << std::endl;
    std::cout << "- `-t [number of threads]`: Set the number of threads, defaults to 1" << std::endl;
    std::cout << "- `-s [number of samples]`: Set the number of samples, defaults to 3" << std::endl;
    std::cout << "- `-b [number of bounces]`: Set the number of bounces, defaults to 2" << std::endl;
    std::cout << "- `-dr [diffusion rays]`: Set the number of diffusion rays, defaults to 1" << std::endl;
    std::cout << "- `-rr [reflection rays]`: Set the number of reflection rays, defaults to 1" << std::endl;
    std::cout << "- `-cli`: Disable the graphical interface for headless execution" << std::endl;
    std::cout << "- `-ne`: Disable preview editor" << std::endl;
    exit(0);
}