/*
** EPITECH PROJECT, 2024
** Vector3D.hpp
** File description:
** raytracer
*/

#pragma once

namespace raytracer
{
    class Vector3D
    {
        public:
            Vector3D(double x = 0, double y = 0, double z = 0);
            ~Vector3D();

            double &GetX() { return _x; }
            double &GetY() { return _y; }
            double &GetZ() { return _z; }

            void SetX(double x) { _x = x; }
            void SetY(double y) { _y = y; }
            void SetZ(double z) { _z = z; }

            Vector3D& operator+(const Vector3D &vec);
            Vector3D& operator+=(const Vector3D &vec);
            Vector3D& operator-(const Vector3D &vec);
            Vector3D& operator-=(const Vector3D &vec);
            Vector3D& operator*(const double &val);
            Vector3D& operator*=(const double &val);
            Vector3D& operator=(const Vector3D &vec);

        private:
            double _x = 0;
            double _y = 0;
            double _z = 0;
    };
}
