/*
** EPITECH PROJECT, 2024
** Threads.cpp
** File description:
** raytracer
*/

#include "Threads.hpp"

raytracer::Threads::Threads() = default;

raytracer::Threads::~Threads() = default;

void raytracer::Threads::startThreads(size_t nbThreads, int chunkWidth, int chunkHeight, Renderer &renderer) {
    _chunks = renderer.getChunks(chunkWidth, chunkHeight);

    for (size_t i = 0; i < nbThreads; i++) {
        _threads.emplace_back([this, &renderer]() {
            while (true) {
                std::unique_lock<std::mutex> lock(_chunksMutex);
                if (_chunks.empty()) {
                    return;
                }
                Chunk chunk = _chunks.back();
                _chunks.pop_back();
                lock.unlock();
                renderer.renderChunk(chunk);
            }
        });
    }
}

void raytracer::Threads::stopThreads()
{
    for (auto &thread : _threads) {
        thread.join();
    }

    _threads.clear();
}
