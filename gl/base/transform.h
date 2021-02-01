//
// Created by mnutec on 2021/1/31.
//

#ifndef MY3D_TRANSFORM_H
#define MY3D_TRANSFORM_H
#include "matrix4.h"
#include "vector4.h"

namespace GLM {

    class Transform {
    public:
        Matrix4f world;
        Matrix4f view;
        Matrix4f projection;
        Matrix4f transform; //transform = world * view * projection;
        float screen_w, screen_h;

        void update();

        void init(int, int);

        void apply(Vector4 &v1, Vector4 &v2);

        void homogenize(Vector4 &y, Vector4 &x);
    };

}
#endif //MY3D_TRANSFORM_H
