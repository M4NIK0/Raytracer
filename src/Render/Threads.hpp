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
            Threads();
            ~Threads();

            void startThreads(size_t nbThreads, int chunkWidth, int chunkHeight, Renderer &renderer);
            void stopThreads();
            size_t getRemainingChunks() { return _chunks.size(); }

        private:
            std::vector<Chunk> _chunks;
            std::vector<std::thread> _threads;
            std::mutex _chunksMutex;
    };
}
