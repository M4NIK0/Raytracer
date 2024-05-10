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
    class editor {
        public:
            editor(Renderer renderer, sfml *display);
            ~editor() = default;
            void run(int windowSize);
            void render();
            void handleEvents();
            void handleKeyboardEvents();
            void handleMouseEvents();
            void handleMouseWheelEvents();

        private:
            void _initImage();

            std::vector<std::vector<RenderRay>> _imageBuffer = {};

            Camera _editorCamera;
            Camera _rendererCamera;
            RenderData _editorData = {};
            RenderData _rendererData = {};

            raytracer::Renderer _renderer;
            sfml *_display;
            bool _isRunning = true;
    };
}
