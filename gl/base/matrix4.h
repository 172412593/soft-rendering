
#ifndef __TYPE_H__
#define __TYPE_H__

#include <initializer_list>
#include "vector4.h"

#include <cstring>

using namespace std;

namespace GLM {



    class Matrix4f {
    public:
        Matrix4f();

        Matrix4f(float f);

        Matrix4f(initializer_list<initializer_list<int>> ilist);

        void init(initializer_list<initializer_list<int>> &ilist);

        float *operator[](int index);

        Matrix4f operator+(Matrix4f &m1);

        Matrix4f operator-(Matrix4f &m1);


        Matrix4f operator*(Matrix4f &m1);

        Matrix4f &operator=(initializer_list<initializer_list<int>> ilist);

        Matrix4f scale(float f) ;

        Vector4 apply(const Vector4&v1);

        void setIdentity();

        void setZero();


    private:
        float m[4][4];
    };
}
#endif