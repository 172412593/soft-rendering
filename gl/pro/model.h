//
// Created by mnutec on 2021/2/1.
//

#ifndef MY3D_MODEL_H
#define MY3D_MODEL_H
#include "../base/Vertex.h"
#include <vector>
#include "../window/Graphic.h"
using namespace std;
namespace GLM {
    class model {
    public:
        vector <Vertex> mesh;

        vector <vector<int>> indices ;

        Matrix4f m;
        void draw(Graphic& g);

        void rotate(float theta,Vector4 v);

        void translate(Vector4 v);

        void scale(Vector4 v);



    };
}

#endif //MY3D_MODEL_H
