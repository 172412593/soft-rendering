//
// Created by mnutec on 2021/1/31.
//

#ifndef MY3D_MATH3D_H
#define MY3D_MATH3D_H






namespace GLM {
//  向量点乘
    class Vector4;
    class Matrix4f;
    Vector4 cross(const Vector4& v1,const Vector4& v2);
// 计算插值：t 为 [0, 1] 之间的数值
    float Interp(float x1, float x2, float t);
    void translate( Matrix4f& m,Vector4& v);
    void scale(Matrix4f& m,Vector4& v);
    void rotate(Matrix4f& m,float theta,Vector4& v);
    void lookAt(Matrix4f& m, Vector4& eye,Vector4& at,Vector4 &up);
    void perspective(Matrix4f &m,float fovy, float aspect,float zn,float zf);
    int check_cvv(const Vector4& v);

}
#endif //MY3D_MATH3D_H
