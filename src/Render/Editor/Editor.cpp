/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editor
*/

#include "Editor.hpp"

raytracer::editor::editor(Renderer renderer, sfml *display) : _editorCamera(renderer.camera), _rendererCamera(renderer.camera), _editorData(renderer.renderData), _rendererData(renderer.renderData), _renderer(renderer), _display(display)
{}

void raytracer::editor::run(int windowSize)
{
    if (windowSize > 0)
    {
        int maxSize = std::max(_renderer.camera.width, _renderer.camera.height);
        double realWidth = (double) _renderer.camera.width / (double) maxSize;
        double realHeight = (double) _renderer.camera.height / (double) maxSize;

        _display->initImage(_renderer.camera.width, _renderer.camera.height);
        _display->initWindow((int) (realWidth * windowSize), (int) (realHeight * windowSize));
    }

    auto begin = std::chrono::steady_clock::now();

    _renderer.initMotions();
    _display->initWindow(800, 600);
    while (_isRunning) {
        handleEvents();
        render();
    }
}

void raytracer::editor::render()
{
    _display->clearWindow();
}

void raytracer::editor::handleEvents()
{
    int event = _display->getEvent();
    if (event == 1) {
        _display->endWindow();
        _isRunning = false;
    }
    handleKeyboardEvents();
    handleMouseEvents();
    handleMouseWheelEvents();
}

void raytracer::editor::handleKeyboardEvents()
{

}

void raytracer::editor::handleMouseEvents()
{

}

void raytracer::editor::handleMouseWheelEvents()
{

}
