//
// Created by mnutec on 2021/1/31.
//

#ifndef MY3D_CAMERA_H
#define MY3D_CAMERA_H

#include "vector4.h"
#include "../window/device.h"
#include "math3d.h"
namespace GLM {
    typedef Vector4 Point;

    class Camera {
    public:
        Point eye,up,at;



        void atZero(Device& device,float x,float y,float z){
            eye={x,y,z,1};
            at = {0,0,0,1};
            up = {0,0,1,1};
            lookAt(device.transform.view,eye,at,up);
            device.transform.update();

        }









    };

}

#endif //MY3D_CAMERA_H
