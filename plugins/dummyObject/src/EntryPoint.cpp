/*
** EPITECH PROJECT, 2024
** EntryPoint.c
** File description:
** dummyLight
*/

#include "../include/IObject.hpp"
#include "Sphere.hpp"

extern "C" raytracer::IObject *getObject() {
    return new raytracer::Sphere();
}
