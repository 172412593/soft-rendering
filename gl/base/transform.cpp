//
// Created by mnutec on 2021/1/31.
//

#include "transform.h"
namespace GLM
{
    void Transform::update()
    {

        transform = world * view * projection;
    }

    // 初始化，设置屏幕长宽
    void Transform::init(int width, int height)
    {
        float aspect = (float)width / ((float)height);
        world.setIdentity();
        view.setIdentity();
        perspective(projection, 3.1415926f * 0.5f, aspect, 1.0f, 500.0f);
        screen_w = (float)width;
        screen_h = (float)height;
        update();
    }

    // 将矢量 x 进行 project
    void Transform::apply(Vector4 &y, Vector4 &x)
    {
        y = transform.apply(x);
    }
    void Transform::homogenize(Vector4 &y, Vector4 &x){
        float rhw = 1.0f / x.w;
	    y.x = (x.x * rhw + 1.0f) * screen_w * 0.5f;
	    y.y = (1.0f - x.y * rhw) * screen_h* 0.5f;
	    y.z = x.z * rhw;
	    y.w = 1.0f;
    }
} // namespace GLM