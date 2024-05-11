/*
** EPITECH PROJECT, 2024
** EntryPoint.c
** File description:
** dummyLight
*/

#include "../../include/ILight.hpp"
#include "DirectionalLight.hpp"

extern "C" arcade::ILight *getLight () {
    return new DirectionalLight();
}
