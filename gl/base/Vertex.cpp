//
// Created by mnutec on 2021/2/1.
//

#include "Vertex.h"

namespace GLM{
    Vertex::Vertex() {

    }

    Vertex::Vertex(Point pos, TexCoord tc, Color color, float rhw):pos(pos),tc(tc),color(color),rhw(rhw){}

    void Vertex::init() {
        float rhw = 1.0f / pos.w;
        this->rhw = rhw;
        tc.u *= rhw;
        tc.v *= rhw;
        color.r *= rhw;
        color.g *= rhw;
        color.b *= rhw;
    }
    Vertex Vertex::interp(Vertex &v1,  float t) {
        Vertex v2;
        v2.pos = pos.interp(v1.pos, t);
        v2.tc.u = Interp(tc.u, v1.tc.u, t);
        v2.tc.v = Interp(tc.v, v1.tc.v, t);
        v2.color.r = Interp(color.r, v1.color.r, t);
        v2.color.g = Interp(color.g, v1.color.g, t);
        v2.color.b = Interp(color.b, v1.color.b, t);
        v2.rhw = Interp(rhw, v1.rhw, t);
        return v2;
    }
    Vertex Vertex::division( Vertex &v1, float w) {
        float inv = 1.0f / w;
        Vertex y;
        y.pos.x = (v1.pos.x - pos.x) * inv;
        y.pos.y = (v1.pos.y - pos.y) * inv;
        y.pos.z = (v1.pos.z - pos.z) * inv;
        y.pos.w = (v1.pos.w - pos.w) * inv;
        y.tc.u = (v1.tc.u - tc.u) * inv;
        y.tc.v = (v1.tc.v - tc.v) * inv;
        y.color.r = (v1.color.r - color.r) * inv;
        y.color.g = (v1.color.g - color.g) * inv;
        y.color.b = (v1.color.b - color.b) * inv;
        y.rhw = (v1.rhw - rhw) * inv;
        return y;
    }

    void Vertex::operator+=(const Vertex &v) {
        pos.x += v.pos.x;
        pos.y += v.pos.y;
        pos.z += v.pos.z;
        pos.w += v.pos.w;
        rhw += v.rhw;
        tc.u += v.tc.u;
        tc.v += v.tc.v;
        color.r += v.color.r;
        color.g += v.color.g;
        color.b += v.color.b;
    }
}