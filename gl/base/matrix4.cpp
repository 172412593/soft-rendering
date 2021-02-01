//
// Created by mnutec on 2021/1/31.
//
#include "matrix4.h"
#include "vector4.h"

namespace GLM {
    Matrix4f::Matrix4f() {
        memset(m, 0, sizeof(m));
    };

    Matrix4f::Matrix4f(float f) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    m[i][j] = f;
                } else {
                    m[i][j] = 0;
                }
            }
        }
    }

    Matrix4f::Matrix4f(initializer_list<initializer_list<int>> ilist) {
        init(ilist);
    }

    void Matrix4f::init(initializer_list<initializer_list<int>> &ilist) {
        if (ilist.size() == 4) {
            initializer_list<initializer_list<int>>::iterator it = ilist.begin();
            for (int i = 0; i < 4; i++) {
                initializer_list<int>::iterator it2 = it->begin();
                for (int j = 0; j < 4; j++) {
                    m[i][j] = *it2;
                    it2++;
                }
                it++;
            }
        }
    }

    float *Matrix4f::operator[](int index) {
        return m[index];
    }

    Matrix4f Matrix4f::operator+(Matrix4f &m1) {
        Matrix4f m2;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m2[i][j] = m[i][i] + m1[i][j];
            }
        }
        return m2;

    }

    Matrix4f Matrix4f::operator-(Matrix4f &m1) {
        Matrix4f m2;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m2[i][j] = m[i][i] - m1[i][j];
            }
        }
        return m2;
    }


    Matrix4f Matrix4f::operator*(Matrix4f &m1) {
        Matrix4f m2;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    m2[i][j] += m[i][k] * m1[k][j];
                }

            }
        }
        return m2;
    }

    Matrix4f &Matrix4f::operator=(initializer_list<initializer_list<int>> ilist) {
        init(ilist);
        return *this;
    }

    Matrix4f Matrix4f::scale(float f) {
        Matrix4f m = *this;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] *= f;
            }
        }
        return m;
    }

    Vector4 Matrix4f::apply(const Vector4 &v1) {
        Vector4 v2;
        v2.x = v1.x * m[0][0] + v1.y * m[1][0] + v1.z * m[2][0] + v1.w * m[3][0];
        v2.y = v1.x * m[0][1] + v1.y * m[1][1] + v1.z * m[2][1] + v1.w * m[3][1];
        v2.z = v1.x * m[0][2] + v1.y * m[1][2] + v1.z * m[2][2] + v1.w * m[3][2];
        v2.w = v1.x * m[0][3] + v1.y * m[1][3] + v1.z * m[2][3] + v1.w * m[3][3];

        return v2;
    }

    void Matrix4f::setIdentity() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    m[i][j] = 1.0f;
                } else {
                    m[i][j] = 0;
                }
            }
        }
    }

    void Matrix4f::setZero() {
        memset(m, 0, sizeof(m));
    }
}