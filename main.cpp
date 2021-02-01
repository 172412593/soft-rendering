#include <iostream>
#include <vector>
#include <GL.h>

using namespace GLM;

float alpha = 1;
bool firstMouse = true;
double lastX,lastY;
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
Camera camera(Vector4(5,0,0,1.0));
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
    Matrix4f view = camera.getViewMatrix();
    window.setView(view);
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
void mouse_callback( double xpos, double ypos)
{

	//如果为第一次进入 记录当前鼠标位置 为初始化鼠标位置
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	//计算当前帧和上一帧的位置差
	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // 这里如果不反过来 实际操作过程中向上移动摄像机 物体也会跟着向上移动 实际应该向下



	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(-yoffset, -xoffset);
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
    window.create(1920, 1080, title);
    window.onDraw = draw;
    window.onMouseMove = mouse_callback;
    window.loop();
    return 0;


}