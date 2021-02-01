//
// Created by mnutec on 2021/1/31.
//

#ifndef MY3D_DEVICE_H
#define MY3D_DEVICE_H

#include "../base/transform.h"


#define RENDER_STATE_WIREFRAME      1		// 渲染线框
#define RENDER_STATE_TEXTURE        2		// 渲染纹理
#define RENDER_STATE_COLOR          4		// 渲染颜色
typedef unsigned int IUINT32;
namespace GLM {
    class Device {
    public:
        Transform transform;
        int width;
        int height;
        IUINT32 **framebuffer;
        float **zbuffer;            // 深度缓存：zbuffer[y] 为第 y行指针
        IUINT32 **texture;          // 纹理：同样是每行索引
        int tex_width;              // 纹理宽度
        int tex_height;             // 纹理高度
        float max_u;                // 纹理最大宽度：tex_width - 1
        float max_v;                // 纹理最大高度：tex_height - 1
        int render_state;           // 渲染状态
        IUINT32 background;         // 背景颜色
        IUINT32 foreground;         // 线框颜色

        void init(int width,int height,void* fb);


        void clear(int i);
    };
}


#endif //MY3D_DEVICE_H
