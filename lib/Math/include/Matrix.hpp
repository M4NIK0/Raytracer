/*
** EPITECH PROJECT, 2024
** Matrix.hpp
** File description:
** raytracer
*/

#pragma once

#include <vector>
#include <iostream>

namespace raytracer
{
    class Matrix
    {
        public:
            Matrix(int x = 1, int y = 1);
            Matrix(std::vector<std::vector<double>> &matrix);
            ~Matrix();

            void set(int x, int y, double value);
            double get(int x, int y) const;
            std::size_t sizeX() const;
            std::size_t sizeY() const;

            Matrix operator*(const Matrix& other) const;
            Matrix operator+(const Matrix& other) const;
            Matrix operator-(const Matrix& other) const;
            Matrix operator*(double value) const;
            Matrix operator/(double value) const;
            Matrix operator=(const Matrix& other);
            Matrix operator=(const std::vector<std::vector<double>>& other);

            std::vector<double>& operator[](std::size_t index);

            raytracer::Matrix transpose();

            class Error : public std::exception
            {
                public:
                    Error(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

        private:
            std::vector<std::vector<double>> matrix;
    };
}
