/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** LibHandler
*/

#include "LibHandler.hpp"

void arcade::LibHandler::openLib(void)
{
    _openLib();
}

arcade::LibHandler::~LibHandler()
{
    closeLib();
}

void arcade::LibHandler::closeLib(void)
{
    _closeLib();
}

bool arcade::LibHandler::checkSymbol(const std::string &symbol)
{
    return _checkSymbol(symbol);
}

void arcade::LibHandler::_openLib()
{
    _handle = dlopen(_path.c_str(), RTLD_LAZY);

    if (!_handle) {
        throw arcade::LibHandler::Error("Cannot open library: " + std::string(dlerror()));
    }
}

void arcade::LibHandler::_closeLib()
{
    if (_handle)
    {
        dlclose(_handle);
        _handle = nullptr;
    }
}

bool arcade::LibHandler::_checkSymbol(const std::string &symbol)
{
    void *sym = dlsym(_handle, symbol.c_str());

    if (!sym)
    {
        return false;
    }

    return true;
}
