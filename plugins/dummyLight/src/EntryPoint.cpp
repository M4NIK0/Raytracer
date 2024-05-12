/*
** EPITECH PROJECT, 2024
** EntryPoint.c
** File description:
** dummyLight
*/

#include "../../../src/Light/ILight.hpp"
#include "DirectionalLight.hpp"

extern "C" raytracer::ILight *getLight() {
    return new raytracer::DirectionalLight();
}
