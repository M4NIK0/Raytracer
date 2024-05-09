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
    double maxColor = 0;

    for (int i = 0; i < _editorData.width; i++)
    {
        for (int j = 0; j < _editorData.height; j++)
        {
            _imageBuffer[i][j] = _renderer.traceEditorRay(i, j);

            if (_imageBuffer[i][j].color.r > maxColor)
                maxColor = _imageBuffer[i][j].color.r;
            if (_imageBuffer[i][j].color.g > maxColor)
                maxColor = _imageBuffer[i][j].color.g;
            if (_imageBuffer[i][j].color.b > maxColor)
                maxColor = _imageBuffer[i][j].color.b;
        }
    }

    for (int i = 0; i < _editorData.width; i++)
    {
        for (int j = 0; j < _editorData.height; j++)
        {
            _imageBuffer[i][j].color.r /= maxColor;
            _imageBuffer[i][j].color.g /= maxColor;
            _imageBuffer[i][j].color.b /= maxColor;
        }
    }
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

void raytracer::editor::_initImage()
{
    _imageBuffer.clear();

    for (int i = 0; i < _editorData.width; i++)
    {
        _imageBuffer.emplace_back();
        for (int j = 0; j < _editorData.width; j++)
        {
            _imageBuffer[i].emplace_back();
        }
    }
}
