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
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    // 默认的摄像机参数
    const float YAW = 180.0f;
    const float PITCH = 0.f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;
    const float PI = 3.1415926f;

    class Camera {
    public:
        Point position, front, up, right;
        Point worldUp;
        float Yaw;
        float Pitch;
        // 摄像机的 移动速度 鼠标灵敏度 视角
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        // void atZero(Device& device,float x,float y,float z){
        //     eye={x,y,z,1};
        //     at = {0,0,0,1};
        //     up = {0,0,1,1};
        //     lookAt(device.transform.view,eye,at,up);
        //     device.transform.update();

        // }

        Camera(Point position = Point(0, 0, 0, 1), Point front = Point(-1, 0, 0, 1), Point up = Point(0, 0, 1, 1),
               Point right = Point(0, 0, 0, 1), float yaw = YAW, float pitch = PITCH, float MovementSpeed = SPEED,
               float MouseSensitivity = SENSITIVITY, float Zoom = ZOOM) : front(front), MovementSpeed(MovementSpeed),
                                                                          MouseSensitivity(MouseSensitivity) {
            this->position = position;
            worldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }

        Matrix4f getViewMatrix() {
            Matrix4f m;
            Point at = position + front;
            GLM::lookAt(m, position, at, up);
            return m;
        }

        void ProcessMouseMovement(double xoffset, double yoffset, bool constrainPitch = true) {
            //防止过速移动 乘以偏移量/鼠标灵敏度
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;
            //更改Pitch与Yaw的值
            Yaw += float(xoffset);
            Pitch += float(yoffset);

            // 确保正确的显示效果 ，为俯仰角度添加限制
            if (constrainPitch) {
                if (Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }

            // 更新摄像机的方向向量
            updateCameraVectors();
        }

        void updateCameraVectors() {
            // 初始化
            Point front;

            front.x = cos(radians(Yaw)) * cos(radians(Pitch));
            front.y = sin(radians(Pitch));
            front.z = sin(radians(Yaw)) * cos(radians(Pitch));
            front.normalize();

            this->front=front;
            // 计算出向上与向右的向量 并归一化
            right = cross(front, worldUp);
            right.normalize();
            up = cross(right, front);
            up.normalize();
        }

        float radians(float theta) {
            float r = theta / 180 * PI;
            return r;
        }
    };

} // namespace GLM

#endif //MY3D_CAMERA_H
