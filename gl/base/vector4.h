//
// Created by mnutec on 2021/1/31.
//

#ifndef MY3D_VECTOR3F_H
#define MY3D_VECTOR3F_H

#include <math.h>
#include "math3d.h"

namespace GLM {
    class Vector4 {
    public:
        float x, y, z, w;

        Vector4() {
            x = y = z = 0;
            w = 1.0;

        }

        Vector4(float x, float y, float z,float w) : x(x), y(y), z(z), w(w) {};

        float length();

        Vector4 operator+(const Vector4 &v1) ;

        Vector4 operator-(const Vector4 &v1) ;


        float operator*(const Vector4 &v);

        Vector4 cross(const Vector4& v1);

        Vector4 interp(const Vector4& v1,float t);

        void normalize();


    };



}
#endif //MY3D_VECTOR3F_H
