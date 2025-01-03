/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Editor
*/

#include "Editor.hpp"

raytracer::Editor::Editor(Renderer &renderer, int windowSize) : _EditorCamera(renderer.camera), _rendererCamera(renderer.camera), _EditorData(renderer.renderData), _rendererData(renderer.renderData), _renderer(renderer), _display(sfml())
{
    int maxSize = std::max(_renderer.camera.width, _renderer.camera.height);
    double realWidth = (double) _renderer.camera.width / (double) maxSize;
    double realHeight = (double) _renderer.camera.height / (double) maxSize;

    _rendererCamera = _renderer.camera;
    _EditorCamera = _renderer.camera;
    _EditorCamera.width = (double)128 * realWidth;
    _EditorCamera.height = (double)128 * realHeight;

    _EditorData.width = _EditorCamera.width;
    _EditorData.height = _EditorCamera.height;

    if (windowSize > 0)
    {
        _display.initImage(_EditorData.width, _EditorData.height);
        _display.initWindow((int) (realWidth * windowSize), (int) (realHeight * windowSize));
    }

    _initImage();
}

void raytracer::Editor::run()
{
    auto begin = std::chrono::steady_clock::now();

    _rendererCamera = _renderer.camera;
    _renderer.camera = _EditorCamera;
    render();
    _displayImage();

    changeResolution(_EditorCamera.width, _EditorCamera.height);
    while (_isRunning) {
        handleEvents();
        if (_EditorCamera.width != _renderer.camera.width) {
            render();
            _displayImage();
        }
    }

    _EditorCamera = _renderer.camera;
    _renderer.camera = _rendererCamera;
}

void raytracer::Editor::render()
{
    double maxColor = 0;

    for (int i = 0; i < _EditorData.width; i++)
    {
        for (int j = 0; j < _EditorData.height; j++)
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
    for (int i = 0; i < _EditorData.width; i++)
    {
        for (int j = 0; j < _EditorData.height; j++)
        {
            _imageBuffer[i][j].color.r = _imageBuffer[i][j].color.r / maxColor * 255;
            _imageBuffer[i][j].color.g = _imageBuffer[i][j].color.g / maxColor * 255;
            _imageBuffer[i][j].color.b = _imageBuffer[i][j].color.b / maxColor * 255;
        }
    }
}

void raytracer::Editor::handleEvents()
{
    int event = _display.getEvent();
    if (event == 1) {
        _display.endWindow();
        _isRunning = false;
    }
    handleKeyboardEvents(event);
    handleMouseEvents(event);
}

void raytracer::Editor::handleKeyboardEvents(int event)
{
    int decreaseRes = 16;
    if (event == 3) {
        _renderer.camera.move(Vector3D(0, 0, -0.1));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 2) {
        _renderer.camera.move(Vector3D(0, 0, 0.1));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 4) {
        _renderer.camera.move(Vector3D(-0.1, 0, 0));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 5) {
        _renderer.camera.move(Vector3D(0.1, 0, 0));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 6) {
        _renderer.camera.move(Vector3D(0, -0.1, 0));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 7) {
        _renderer.camera.move(Vector3D(0, 0.1, 0));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 15) {
        _renderer.camera.rotate(Vector3D(-0.5, 0, 0));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 14) {
        _renderer.camera.rotate(Vector3D(0.5, 0, 0));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 13) {
        _renderer.camera.rotate(Vector3D(0, 0, -0.5));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 12) {
        _renderer.camera.rotate(Vector3D(0, 0, 0.5));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 11) {
        _renderer.camera.rotate(Vector3D(0, -0.5, 0));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 10) {
        _renderer.camera.rotate(Vector3D(0, 0.5, 0));
        changeResolution(_EditorCamera.width / decreaseRes, _EditorCamera.height / decreaseRes);
    }
    if (event == 0)
        if (_renderer.camera.width < _EditorCamera.width && _renderer.camera.height < _EditorCamera.height)
            changeResolution(_renderer.camera.width + 20, _renderer.camera.height + 10);
        else
            changeResolution(_EditorData.width, _EditorData.height);
}

void raytracer::Editor::handleMouseEvents(int event)
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

void raytracer::Editor::_displayImage()
{
    for (int i = 0; i < _EditorData.width; i++)
    {
        for (int j = 0; j < _EditorData.height; j++)
        {
            _display.drawPixel(i, j, _imageBuffer[i][j].color);
        }
    }
    _display.displayScreen();
}

void raytracer::Editor::changeResolution(int width, int height)
{
    _renderer.camera.width = width;
    _renderer.camera.height = height;
    _EditorData.width = width;
    _EditorData.height = height;
    _display.initImage(width, height);
    _initImage();
}
