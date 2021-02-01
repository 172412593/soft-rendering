//
// Created by mnutec on 2021/1/31.
//

#include "vector4.h"
namespace GLM {

    float Vector4::length() {
        return sqrt(x * x + y * y + z * z);

    }
    Vector4 Vector4::operator+(const Vector4 &v1) {
        Vector4 v2;
        v2.x = x + v1.x;
        v2.y = y + v1.y;
        v2.z = z + v1.z;
        return v2;

    }

    Vector4 Vector4::operator-(const Vector4 &v1) {
        Vector4 v2;
        v2.x = x - v1.x;
        v2.y = y - v1.y;
        v2.z = z - v1.z;
        return v2;
    }


    float Vector4::operator*(const Vector4 &v) {

        return x * v.x + y * v.y + z * v.z;
    }

    Vector4 Vector4::cross(const Vector4 &v1) {
        Vector4 v2 = GLM::cross(*this, v1);
        return v2;
    }

    Vector4 Vector4::interp(const Vector4 &v1, float t) {
        Vector4 v2;
        v2.x = GLM::Interp(x, v1.x, t);
        v2.y = GLM::Interp(y, v1.y, t);
        v2.z = GLM::Interp(z, v1.z, t);
        return v2;

    }

    void Vector4::normalize() {
        float length = this->length();
        if (length != 0.0f) {
            float inv = 1.0f / length;
            x *= inv;
            y *= inv;
            z *= inv;

        }
    }
}