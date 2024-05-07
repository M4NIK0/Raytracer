/*
** EPITECH PROJECT, 2024
** Threads.hpp
** File description:
** raytracer
*/

#pragma once

#include <thread>
#include <mutex>
#include "Renderer.hpp"

namespace raytracer
{
    class Threads
    {
        public:
            class Error : public std::exception
            {
                public:
                    Error(std::string const &message) :
                        _message(message) {};

                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message;
            };

            Threads(Renderer &renderer);
            ~Threads();

            void startThreads(size_t nbThreads, int chunkWidth, int chunkHeight);
            void stopThreads();
            size_t getRemainingChunks() { return _chunks.size(); }

        private:
            Renderer &_renderer;
            std::vector<Chunk> _chunks;
            std::vector<std::thread> _threads;
            std::mutex _chunksMutex;
    };
}
