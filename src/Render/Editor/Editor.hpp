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
            void handleKeyboardEvents();
            void handleMouseEvents();
            void handleMouseWheelEvents();

        private:
            void _initImage();

            std::vector<std::vector<RenderRay>> _imageBuffer = {};

            Camera _EditorCamera;
            Camera _rendererCamera;
            RenderData _EditorData = {};
            RenderData _rendererData = {};

            raytracer::Renderer _renderer;
            sfml *_display;
            bool _isRunning = true;
    };
}
