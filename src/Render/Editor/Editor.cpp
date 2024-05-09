/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Editor
*/

#include "Editor.hpp"

void raytracer::Editor::renderObject()
{

}

raytracer::Editor::Editor(Renderer &renderer, int windowSize) : _EditorCamera(renderer.camera), _rendererCamera(renderer.camera), _EditorData(renderer.renderData), _rendererData(renderer.renderData), _renderer(renderer), _display(sfml())
{
    if (windowSize > 0)
    {
        int maxSize = std::max(_renderer.camera.width, _renderer.camera.height);
        double realWidth = (double) _renderer.camera.width / (double) maxSize;
        double realHeight = (double) _renderer.camera.height / (double) maxSize;

        _display.initImage(_renderer.camera.width, _renderer.camera.height);
        _display.initWindow((int) (realWidth * windowSize), (int) (realHeight * windowSize));
    }
}

void raytracer::Editor::run(int windowSize)
{
    auto begin = std::chrono::steady_clock::now();

    _renderer.initMotions();
    _display.initWindow(800, 600);
    while (_isRunning) {
        handleEvents();
        render();
    }
}

void raytracer::Editor::render()
{
    double maxColor = 0;
    for (int i = 0; i < _renderer.renderData.width; i++) {
        for (int j = 0; j < _renderer.renderData.height; j++) {
            raytracer::RenderRay ray = _renderer.traceEditorRay(i, j);

            _imageBuffer[i][j] = ray;

            if (ray.color.r > maxColor)
            {
                maxColor = ray.color.r;
            }
            if (ray.color.g > maxColor)
            {
                maxColor = ray.color.g;
            }
            if (ray.color.b > maxColor)
            {
                maxColor = ray.color.b;
            }
        }
    }

    for (int i = 0; i < _renderer.renderData.width; i++) {
        for (int j = 0; j < _renderer.renderData.height; j++) {
            Color color = _imageBuffer[i][j].color;

            color.r = color.r / maxColor * 255;
            color.g = color.g / maxColor * 255;
            color.b = color.b / maxColor * 255;

            _display.drawPixel(i, j, color);
        }
    }

    _display.displayScreen();
}

void raytracer::Editor::handleEvents()
{
    int event = _display.getEvent();
    if (event == 1) {
        _display.endWindow();
        _isRunning = false;
    }
    handleKeyboardEvents();
    handleMouseEvents();
    handleMouseWheelEvents();
}

void raytracer::Editor::handleKeyboardEvents()
{

}

void raytracer::Editor::handleMouseEvents()
{

}

void raytracer::Editor::handleMouseWheelEvents()
{

}
