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
            Matrix(int x = 1, int y = 1) : matrix(std::vector<std::vector<double>>(x, std::vector<double>(y, 0))) {};
            Matrix(std::vector<std::vector<double>> &matrix) : matrix(matrix) {};
            ~Matrix();

            void set(int x, int y, double value) { matrix[x][y] = value; }
            double get(int x, int y) const { return matrix[x][y]; }
            std::size_t sizeX() const { return matrix.size(); }
            std::size_t sizeY() const { return matrix[0].size(); }

            Matrix operator*(const Matrix& other) const;
            Matrix operator+(const Matrix& other) const;
            Matrix operator-(const Matrix& other) const;
            Matrix operator*(double value) const;
            Matrix operator/(double value) const;
            Matrix operator=(const Matrix& other);
            Matrix operator=(const std::vector<std::vector<double>>& other);

            std::vector<double>& operator[](std::size_t index) { return matrix[index]; }

            class Error : public std::exception
            {
                public:
                    Error(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            raytracer::Matrix transpose();

        private:
            std::vector<std::vector<double>> matrix;
    };
}
