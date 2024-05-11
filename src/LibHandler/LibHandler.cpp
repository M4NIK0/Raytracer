/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** LibHandler
*/

#include "LibHandler.hpp"

void raytracer::LibHandler::openLib(void)
{
    _openLib();
}

raytracer::LibHandler::~LibHandler()
{
    closeLib();
}

void raytracer::LibHandler::closeLib(void)
{
    _closeLib();
}

bool raytracer::LibHandler::checkSymbol(const std::string &symbol)
{
    return _checkSymbol(symbol);
}

void raytracer::LibHandler::_openLib()
{
    _handle = dlopen(_path.c_str(), RTLD_LAZY);

    if (!_handle) {
        throw raytracer::LibHandler::Error("Cannot open library: " + std::string(dlerror()));
    }
}

void raytracer::LibHandler::_closeLib()
{
    if (_handle)
    {
        dlclose(_handle);
        _handle = nullptr;
    }
}

bool raytracer::LibHandler::_checkSymbol(const std::string &symbol)
{
    void *sym = dlsym(_handle, symbol.c_str());

    if (!sym)
    {
        return false;
    }

    return true;
}
