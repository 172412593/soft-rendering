//
// Created by mnutec on 2021/2/1.
//

#ifndef MY3D_VERTEX_H
#define MY3D_VERTEX_H
#include "vector4.h"

namespace GLM {
    typedef Vector4 Point;
    struct Color {
        float r, g, b;

        Color() : r(0), g(0), b(0) {}

        Color(float r, float g, float b) : r(r), g(g), b(b) {};
    };

    struct TexCoord {
        float u, v;

        TexCoord() : u(0), v(0){};

        TexCoord(float u, float v) : u(u), v(v) {};
    };

    class Vertex {
    public:

        Point pos;
        TexCoord tc;
        Color color;
        float rhw;

        Vertex();
        Vertex(Point pos,TexCoord tc,Color color, float rhw);
        Vertex interp(Vertex& v1,float t);
        Vertex division(Vertex& v1,float w);

        void operator+=(const Vertex& v);
        void init();
    };



}
#endif //MY3D_VERTEX_H
