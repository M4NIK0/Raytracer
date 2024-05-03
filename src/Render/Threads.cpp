/*
** EPITECH PROJECT, 2024
** Threads.cpp
** File description:
** raytracer
*/

#include "Threads.hpp"

raytracer::Threads::Threads(Renderer &renderer) : _renderer(renderer) {}

raytracer::Threads::~Threads() = default;

void raytracer::Threads::startThreads(size_t nbThreads, int chunkWidth, int chunkHeight)
{
    _chunks = _renderer.getChunks(chunkWidth, chunkHeight);

    for (size_t i = 0; i < nbThreads; i++) {
        std::cout << "starting thread " << i << std::endl;
        _threads.emplace_back([this]() {
            while (true) {
                std::unique_lock<std::mutex> lock(_chunksMutex);
                if (_chunks.empty()) {
                    return;
                }
                Chunk chunk = _chunks.back();
                _chunks.pop_back();
                lock.unlock();
                _renderer.renderChunk(chunk);
            }
        });
    }
}

void raytracer::Threads::stopThreads()
{
    for (auto &thread : _threads) {
        thread.join();
    }
}
