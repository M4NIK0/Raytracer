/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Editor
*/

#pragma once

#include "../Renderer.hpp"
#include "../../sfml/sfml.hpp"

namespace raytracer {
    class Editor {
        public:
            Editor(Renderer &renderer, int windowSize);
            ~Editor() = default;
            void run();
            void render();
            void handleEvents();
            void handleKeyboardEvents(int event);
            void handleMouseEvents(int event);
            void changeResolution(int width, int height);

        private:
            void _initImage();
            void _displayImage();
            Camera _EditorCamera;
            Camera _rendererCamera;
            RenderData _EditorData = {};
            RenderData _rendererData = {};

            std::vector<std::vector<RenderRay>> _imageBuffer = {};

            raytracer::Renderer &_renderer;
            sfml _display;
            bool _isRunning = true;
    };
}
