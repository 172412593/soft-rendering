//
// Created by mnutec on 2021/1/31.
//

#include "Graphic.h"
namespace GLM {
    int CMID(int x, int min, int max) { return (x < min) ? min : ((x > max) ? max : x); }

    void Graphic::device_pixel( int x, int y, IUINT32 color) {
        if (((IUINT32) x) < (IUINT32) device->width && ((IUINT32) y) < (IUINT32) device->height) {
            device->framebuffer[y][x] = color;
        }
    }

// 绘制线段
    void Graphic::device_draw_line( int x1, int y1, int x2, int y2, IUINT32 c) {
        int x, y, rem = 0;
        if (x1 == x2 && y1 == y2) {
            device_pixel( x1, y1, c);
        } else if (x1 == x2) {
            int inc = (y1 <= y2) ? 1 : -1;
            for (y = y1; y != y2; y += inc) device_pixel( x1, y, c);
            device_pixel( x2, y2, c);
        } else if (y1 == y2) {
            int inc = (x1 <= x2) ? 1 : -1;
            for (x = x1; x != x2; x += inc) device_pixel( x, y1, c);
            device_pixel( x2, y2, c);
        } else {
            int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
            int dy = (y1 < y2) ? y2 - y1 : y1 - y2;
            if (dx >= dy) {
                if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
                for (x = x1, y = y1; x <= x2; x++) {
                    device_pixel( x, y, c);
                    rem += dy;
                    if (rem >= dx) {
                        rem -= dx;
                        y += (y2 >= y1) ? 1 : -1;
                        device_pixel( x, y, c);
                    }
                }
                device_pixel( x2, y2, c);
            } else {
                if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
                for (x = x1, y = y1; y <= y2; y++) {
                    device_pixel( x, y, c);
                    rem += dx;
                    if (rem >= dy) {
                        rem -= dy;
                        x += (x2 >= x1) ? 1 : -1;
                        device_pixel( x, y, c);
                    }
                }
                device_pixel( x2, y2, c);
            }
        }
    }

// 根据坐标读取纹理
    IUINT32 Graphic::device_texture_read(float u, float v) {
        int x, y;
        u = u * device->max_u;
        v = v * device->max_v;
        x = (int) (u + 0.5f);
        y = (int) (v + 0.5f);
        x = CMID(x, 0, device->tex_width - 1);
        y = CMID(y, 0, device->tex_height - 1);
        return device->texture[y][x];
    }


//=====================================================================
// 渲染实现
//=====================================================================

// 绘制扫描线
    void Graphic::device_draw_scanline( scanline_t *scanline) {
        IUINT32 *framebuffer = device->framebuffer[scanline->y];
        float *zbuffer = device->zbuffer[scanline->y];
        int x = scanline->x;
        int w = scanline->w;
        int width = device->width;
        int render_state = device->render_state;
        for (; w > 0; x++, w--) {
            if (x >= 0 && x < width) {
                float rhw = scanline->v.rhw;
                if (rhw >= zbuffer[x]) {
                    float w = 1.0f / rhw;
                    zbuffer[x] = rhw;
                    if (render_state & RENDER_STATE_COLOR) {
                        float r = scanline->v.color.r * w;
                        float g = scanline->v.color.g * w;
                        float b = scanline->v.color.b * w;
                        int R = (int) (r * 255.0f);
                        int G = (int) (g * 255.0f);
                        int B = (int) (b * 255.0f);
                        R = CMID(R, 0, 255);
                        G = CMID(G, 0, 255);
                        B = CMID(B, 0, 255);
                        framebuffer[x] = (R << 16) | (G << 8) | (B);
                    }
                    if (render_state & RENDER_STATE_TEXTURE) {
                        float u = scanline->v.tc.u * w;
                        float v = scanline->v.tc.v * w;
                        IUINT32 cc = device_texture_read( u, v);
                        framebuffer[x] = cc;
                    }
                }
            }
            scanline->v+=scanline->step;
            if (x >= width) break;
        }
    }
    void Graphic::trapezoid_edge_interp(trapezoid_t *trap, float y) {
        float s1 = trap->left.v2.pos.y - trap->left.v1.pos.y;
        float s2 = trap->right.v2.pos.y - trap->right.v1.pos.y;
        float t1 = (y - trap->left.v1.pos.y) / s1;
        float t2 = (y - trap->right.v1.pos.y) / s2;
        trap->left.v= trap->left.v1.interp(trap->left.v2, t1);
        trap->right.v=trap->right.v1.interp(trap->right.v2, t2);
    }

// 根据左右两边的端点，初始化计算出扫描线的起点和步长
    void Graphic::trapezoid_init_scan_line(trapezoid_t *trap, scanline_t *scanline, int y) {
        float width = trap->right.v.pos.x - trap->left.v.pos.x;
        scanline->x = (int)(trap->left.v.pos.x + 0.5f);
        scanline->w = (int)(trap->right.v.pos.x + 0.5f) - scanline->x;
        scanline->y = y;
        scanline->v = trap->left.v;
        if (trap->left.v.pos.x >= trap->right.v.pos.x) scanline->w = 0;
        scanline->step= trap->left.v.division(trap->right.v, width);
    }
// 主渲染函数
    void Graphic::device_render_trap( trapezoid_t *trap) {
        scanline_t scanline;
        int j, top, bottom;
        top = (int) (trap->top + 0.5f);
        bottom = (int) (trap->bottom + 0.5f);
        for (j = top; j < bottom; j++) {
            if (j >= 0 && j < device->height) {
                trapezoid_edge_interp(trap, (float) j + 0.5f);
                trapezoid_init_scan_line(trap, &scanline, j);
                device_draw_scanline( &scanline);
            }
            if (j >= device->height) break;
        }
    }
    int Graphic::trapezoid_init_triangle(trapezoid_t *trap, const Vertex *p1,
                                const Vertex *p2, const Vertex *p3) {
        const Vertex *p;
        float k, x;

        if (p1->pos.y > p2->pos.y) p = p1, p1 = p2, p2 = p;
        if (p1->pos.y > p3->pos.y) p = p1, p1 = p3, p3 = p;
        if (p2->pos.y > p3->pos.y) p = p2, p2 = p3, p3 = p;
        if (p1->pos.y == p2->pos.y && p1->pos.y == p3->pos.y) return 0;
        if (p1->pos.x == p2->pos.x && p1->pos.x == p3->pos.x) return 0;

        if (p1->pos.y == p2->pos.y) {	// triangle down
            if (p1->pos.x > p2->pos.x) p = p1, p1 = p2, p2 = p;
            trap[0].top = p1->pos.y;
            trap[0].bottom = p3->pos.y;
            trap[0].left.v1 = *p1;
            trap[0].left.v2 = *p3;
            trap[0].right.v1 = *p2;
            trap[0].right.v2 = *p3;
            return (trap[0].top < trap[0].bottom)? 1 : 0;
        }

        if (p2->pos.y == p3->pos.y) {	// triangle up
            if (p2->pos.x > p3->pos.x) p = p2, p2 = p3, p3 = p;
            trap[0].top = p1->pos.y;
            trap[0].bottom = p3->pos.y;
            trap[0].left.v1 = *p1;
            trap[0].left.v2 = *p2;
            trap[0].right.v1 = *p1;
            trap[0].right.v2 = *p3;
            return (trap[0].top < trap[0].bottom)? 1 : 0;
        }

        trap[0].top = p1->pos.y;
        trap[0].bottom = p2->pos.y;
        trap[1].top = p2->pos.y;
        trap[1].bottom = p3->pos.y;

        k = (p3->pos.y - p1->pos.y) / (p2->pos.y - p1->pos.y);
        x = p1->pos.x + (p2->pos.x - p1->pos.x) * k;

        if (x <= p3->pos.x) {		// triangle left
            trap[0].left.v1 = *p1;
            trap[0].left.v2 = *p2;
            trap[0].right.v1 = *p1;
            trap[0].right.v2 = *p3;
            trap[1].left.v1 = *p2;
            trap[1].left.v2 = *p3;
            trap[1].right.v1 = *p1;
            trap[1].right.v2 = *p3;
        }	else {					// triangle right
            trap[0].left.v1 = *p1;
            trap[0].left.v2 = *p3;
            trap[0].right.v1 = *p1;
            trap[0].right.v2 = *p2;
            trap[1].left.v1 = *p1;
            trap[1].left.v2 = *p3;
            trap[1].right.v1 = *p2;
            trap[1].right.v2 = *p3;
        }

        return 2;
    }
// 根据 render_state 绘制原始三角形
    void Graphic::device_draw_primitive(  Vertex *v1,
                                 Vertex *v2,  Vertex *v3) {
        Point p1, p2, p3, c1, c2, c3;
        int render_state = device->render_state;

        // 按照 Transform 变化
        device->transform.apply(c1, v1->pos);
        device->transform.apply( c2, v2->pos);
        device->transform.apply( c3, v3->pos);

        // 裁剪，注意此处可以完善为具体判断几个点在 cvv内以及同cvv相交平面的坐标比例
        // 进行进一步精细裁剪，将一个分解为几个完全处在 cvv内的三角形
        if (check_cvv(c1) != 0) return;
        if (check_cvv(c2) != 0) return;
        if (check_cvv(c3) != 0) return;

        // 归一化
        device->transform.homogenize(p1, c1);
        device->transform.homogenize(p2, c2);
        device->transform.homogenize(p3, c3);

        // 纹理或者色彩绘制
        if (render_state & (RENDER_STATE_TEXTURE | RENDER_STATE_COLOR)) {
            Vertex t1 = *v1, t2 = *v2, t3 = *v3;
            trapezoid_t traps[2];
            int n;

            t1.pos = p1;
            t2.pos = p2;
            t3.pos = p3;
            t1.pos.w = c1.w;
            t2.pos.w = c2.w;
            t3.pos.w = c3.w;

            t1.init();    // 初始化 w
            t2.init();   // 初始化 w
            t3.init();   // 初始化 w

            // 拆分三角形为0-2个梯形，并且返回可用梯形数量
            n = trapezoid_init_triangle(traps, &t1, &t2, &t3);

            if (n >= 1) device_render_trap( &traps[0]);
            if (n >= 2) device_render_trap( &traps[1]);
        }

        if (render_state & RENDER_STATE_WIREFRAME) {        // 线框绘制
            device_draw_line( (int) p1.x, (int) p1.y, (int) p2.x, (int) p2.y, device->foreground);
            device_draw_line( (int) p1.x, (int) p1.y, (int) p3.x, (int) p3.y, device->foreground);
            device_draw_line( (int) p3.x, (int) p3.y, (int) p2.x, (int) p2.y, device->foreground);
        }
    }

    void Graphic::draw_plane( int a, int b, int c, int d) {
        Vertex p1 = (*mesh)[a], p2 = (*mesh)[b], p3 = (*mesh)[c], p4 = (*mesh)[d];
        p1.tc.u = 0, p1.tc.v = 0, p2.tc.u = 0, p2.tc.v = 1;
        p3.tc.u = 1, p3.tc.v = 1, p4.tc.u = 1, p4.tc.v = 0;
        device_draw_primitive( &p1, &p2, &p3);
        device_draw_primitive( &p3, &p4, &p1);
    }

    void Graphic::draw_box( float theta) {
        Matrix4f m;
        Vector4 v(-1, -0.5, 1,1.0);
        rotate(m,theta,v);
        device->transform.world = m;
        device->transform.update();

        draw_plane( 0, 1, 2, 3);
        draw_plane( 7, 6, 5, 4);
        draw_plane( 0, 4, 5, 1);
        draw_plane( 1, 5, 6, 2);
        draw_plane( 2, 6, 7, 3);
        draw_plane( 3, 7, 4, 0);
    }



    void Graphic::VertexPointer(std::vector<Vertex> *mesh) {
        this->mesh = mesh;
    }

    void Graphic::drawElement(std::vector<std::vector<int>> *indices) {
        this->indices = indices;
        for(vector<int> v:*indices){
            draw_plane(v[0],v[1],v[2],v[3]);
        }

    }

    void Graphic::loadMatrix(Matrix4f &mat) {
        device->transform.world = mat;
        device->transform.update();
    }
}