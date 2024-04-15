#include <iostream>
#include <random>

#include "sfml/sfml.hpp"

raytracer::Color generateNoise()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    return raytracer::Color(dis(gen), dis(gen), dis(gen));
}

int main() {
    sfml display;

    // Initialize the window
    display.initWindow();

    // Generate noise for each pixel
    for (int x = 0; x < 800; ++x) {
        for (int y = 0; y < 600; ++y) {
            display.drawPixel(x, y, generateNoise());
        }
        display.displayScreen();
    }

    bool loop = true;
    while (loop)
    {
        if (display.getEvent() == 1)
            loop = false;
    }

    // End the window
    display.endWindow();

    return 0;
}
