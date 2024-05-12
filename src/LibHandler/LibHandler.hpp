/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** LibHandler
*/

#ifndef LIBHANDLER_HPP_
#define LIBHANDLER_HPP_

#include <dlfcn.h>
#include <iostream>
#include <memory>

namespace raytracer
{
    class LibHandler
    {
        public:
            LibHandler() : _handle(nullptr) {}
            LibHandler(std::string &path) : _path(path), _handle(nullptr) {}
            ~LibHandler();

            void setPath(const std::string &path) { _path = path; }

            void openLib();
            void closeLib();

            bool checkSymbol(const std::string &symbol);

            template<typename T>
            std::shared_ptr<T> getObject(std::string &symbol)
            {
                return _getObject<T>(symbol);
            }

            class Error : public std::exception
            {
                public:
                    Error(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }

                private:
                    std::string _message;
            };

        private:

            std::string _path;
            void *_handle{};

            template<typename T>
            std::shared_ptr<T> _getObject(std::string &symbol)
            {
                T *(*sym)() = reinterpret_cast<T *(*)()>(dlsym(_handle, symbol.c_str()));
                const char *dlsym_error = dlerror();

                if (dlsym_error) {
                    throw raytracer::LibHandler::Error("Cannot load symbol:" + std::string(dlsym_error));
                }

                std::shared_ptr<T> obj(sym());

                return obj;
            }

            void _openLib(void);
            void _closeLib(void);
            bool _checkSymbol(const std::string &symbol);
    };
}

#endif /* !LIBHANDLER_HPP_ */
