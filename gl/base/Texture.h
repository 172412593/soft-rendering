//
// Created by mnutec on 2021/1/31.
//

#ifndef MY3D_TEXTURE_H
#define MY3D_TEXTURE_H
#include "../window/device.h"
#include <assert.h>
namespace GLM {
    class Texture {
    public:
        IUINT32 data[256][256];

        void init();

        void bind(Device &device);
    };
}

#endif //MY3D_TEXTURE_H
