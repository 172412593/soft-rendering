#include <iostream>
#include <vector>
#include <GL.h>

using namespace GLM;

float alpha = 1;

vector<Vertex> mesh = {
        {{-1, -1, 1,  1}, {0, 0}, {1.0f, 0.2f, 0.2f}, 1},
        {{1,  -1, 1,  1}, {0, 1}, {0.2f, 1.0f, 0.2f}, 1},
        {{1,  1,  1,  1}, {1, 1}, {0.2f, 0.2f, 1.0f}, 1},
        {{-1, 1,  1,  1}, {1, 0}, {1.0f, 0.2f, 1.0f}, 1},
        {{-1, -1, -1, 1}, {0, 0}, {1.0f, 1.0f, 0.2f}, 1},
        {{1,  -1, -1, 1}, {0, 1}, {0.2f, 1.0f, 1.0f}, 1},
        {{1,  1,  -1, 1}, {1, 1}, {1.0f, 0.3f, 0.3f}, 1},
        {{-1, 1,  -1, 1}, {1, 0}, {0.2f, 1.0f, 0.3f}, 1},
};

vector<vector<int>> indices={{0,1,2,3},{7,6,5,4},{0,4,5,1},{1,5,6,2},{2,6,7,3},{3,7,4,0}};

void draw(GLWindow &window) {
    Graphic graphic = window.createGraphic();
//    if (window.getKeyState(VK_LEFT)) alpha += 0.01f;
//    if (window.getKeyState(VK_RIGHT)) alpha -= 0.01f;
    alpha+=0.01f;
//    Matrix4f m;
    Vector4 v(-1, -0.5, 1,1.0);
//    rotate(m,alpha,v);
//    graphic.loadMatrix(m);
//    graphic.VertexPointer(&mesh);
//    graphic.drawElement(&indices);
    Cube cube;
    cube.rotate(alpha,v);
    Vector4 tv(0.0,1.5,0,1.0);
    cube.translate(tv);
    cube.draw(graphic);
    Cube cube1;
    cube1.rotate(alpha,v);
    Vector4 tv2(0.0,-1.5,0,1.0);
    cube1.scale(Vector4(0.5,0.5,0.5,1.0));
    cube1.translate(tv2);
    cube1.draw(graphic);


}

int main() {
    Matrix4f m = {{1, 2, 3, 4},
                  {5, 6, 7, 8},
                  {1, 2, 3, 4},
                  {5, 6, 7, 8}};
    Matrix4f m1 = {{1, 1, 1, 1},
                   {2, 2, 2, 2},
                   {3, 3, 3, 3},
                   {4, 4, 4, 4}};
    Matrix4f m2 = m + m1;
    Matrix4f m3 = m * m1;
    m = {{1, 1, 1, 1},
         {2, 2, 2, 2},
         {3, 3, 3, 3},
         {4, 4, 4, 4}};
    Vector4 v(1.0, 2.0, 3.0, 1.0);
    Vector4 v1(1, 1, 1, 1);
    Vector4 v2 = v.cross(v1);
    Matrix4f trans;
    GLM::translate(trans, v1);
    GLWindow window;




    TCHAR *title = _T("Mini3d (software render tutorial) - ")
                   _T("Left/Right: rotation, Up/Down: forward/backward, Space: switch state");
    window.create(800, 600, title);
    window.onDraw = draw;
    window.loop();
    return 0;


}