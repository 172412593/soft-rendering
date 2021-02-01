//
// Created by mnutec on 2021/1/31.
//

#ifndef MY3D_GRAPHIC_H
#define MY3D_GRAPHIC_H
#include "../base/math3d.h"
#include "device.h"
#include "../base/vector3.h"
#include "../base/Vertex.h"
#include <vector>
namespace GLM {
    typedef struct {
        Vertex v, v1, v2;
    } edge_t;
    typedef struct {
        float top, bottom;
        edge_t left, right;
    } trapezoid_t;
    typedef struct {
        Vertex v, step;
        int x, y, w;
    } scanline_t;

    int CMID(int x, int min, int max);

    class Graphic {
    private:
        Device *device;
        std::vector<Vertex>* mesh;

        std::vector<std::vector<int>>* indices;

    public:
        Graphic(Device *device){
            this->device = device;
        }


        void loadMatrix(Matrix4f &mat);


        void VertexPointer(std::vector<Vertex>* mesh);
        void drawElement(std::vector<std::vector<int>>* indices);

        void device_pixel( int x, int y, IUINT32 color);

// 绘制线段
        void device_draw_line( int x1, int y1, int x2, int y2, IUINT32 c);

// 根据坐标读取纹理
        IUINT32 device_texture_read(float u, float v) ;


//=====================================================================
// 渲染实现
//=====================================================================

// 绘制扫描线
        void device_draw_scanline( scanline_t *scanline) ;
        void trapezoid_edge_interp(trapezoid_t *trap, float y);

// 根据左右两边的端点，初始化计算出扫描线的起点和步长
        void trapezoid_init_scan_line(trapezoid_t *trap, scanline_t *scanline, int y) ;
// 主渲染函数
        void device_render_trap( trapezoid_t *trap);
        int trapezoid_init_triangle(trapezoid_t *trap, const Vertex *p1,
                                    const Vertex *p2, const Vertex *p3) ;
// 根据 render_state 绘制原始三角形
        void device_draw_primitive(  Vertex *v1,
                                     Vertex *v2,  Vertex *v3);

        void draw_plane( int a, int b, int c, int d) ;

        void draw_box( float theta);
    };
}

#endif //MY3D_GRAPHIC_H
