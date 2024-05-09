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
    _display->clearWindow();
}

void raytracer::editor::handleEvents()
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

void raytracer::Editor::_initImage()
{
    _imageBuffer.clear();

    for (int i = 0; i < _EditorData.width; i++)
    {
        _imageBuffer.emplace_back();
        for (int j = 0; j < _EditorData.width; j++)
        {
            _imageBuffer[i].emplace_back();
        }
    }
}
