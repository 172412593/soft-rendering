//
// Created by mnutec on 2021/1/31.
//

#include "Texture.h"
namespace GLM{
    void Texture::init() {
        int i, j;
        for (j = 0; j < 256; j++) {
            for (i = 0; i < 256; i++) {
                int x = i / 32, y = j / 32;
                data[j][i] = ((x + y) & 1) ? 0xffffff : 0x3fbcef;
            }
        }
    }

    void Texture::bind(Device &device) {
        int pitch = 256*4;
        int w=256,h=256;

        char *ptr = (char*)data;
        int j;
        assert(w <= 1024 && h <= 1024);
        for (j = 0; j < h; ptr += pitch, j++) 	// 重新计算每行纹理的指针
            device.texture[j] = (IUINT32*)ptr;
        device.tex_width = w;
        device.tex_height = h;
        device.max_u = (float)(w - 1);
        device.max_v = (float)(h - 1);
    }
}