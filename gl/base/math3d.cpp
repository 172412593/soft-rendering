//
// Created by mnutec on 2021/1/31.
//

#include "math3d.h"
#include "vector4.h"
#include "matrix4.h"
namespace GLM {

    Vector4 cross(const Vector4 &v1, const Vector4 &v2) {

        Vector4 v;
        float x, y, z;
        x = v1.y * v2.z - v1.z * v2.y;
        y = v1.z * v2.x - v1.x * v2.z;
        z = v1.x * v2.y - v1.y * v2.x;
        v.x = x;
        v.y = y;
        v.z = z;
        return v;

    }

    float Interp(float x1, float x2, float t) {
        return x1 + (x2 - x1) * t;
    }

    void translate(Matrix4f &m, Vector4& v) {


        m.setIdentity();
        m[3][0] = v.x;
        m[3][1] = v.y;
        m[3][2] = v.z;

        

    }

    void scale(Matrix4f& m,Vector4& v){

        m.setIdentity();
        m[0][0] = v.x;
        m[1][1] = v.y;
        m[2][2] = v.z;

        


    }

    void rotate(Matrix4f& m,float theta,Vector4& v){
       
        float qsin = (float)sin(theta*0.5);
        float qcos = (float)cos(theta*0.5);
        Vector4  vec(v.x,v.y,v.z,1.0f);
        float w = qcos;
        vec.normalize();
        float x = vec.x*qsin;
        float y = vec.y*qsin;
        float z = vec.z*qsin;
        m[0][0] = 1 - 2 * y * y - 2 * z * z;
        m[1][0] = 2 * x * y - 2 * w * z;
        m[2][0] = 2 * x * z + 2 * w * y;
        m[0][1] = 2 * x * y + 2 * w * z;
        m[1][1] = 1 - 2 * x * x - 2 * z * z;
        m[2][1] = 2 * y * z - 2 * w * x;
        m[0][2] = 2 * x * z - 2 * w * y;
        m[1][2] = 2 * y * z + 2 * w * x;
        m[2][2] = 1 - 2 * x * x - 2 * y * y;
        m[0][3] = m[1][3] = m[2][3] = 0.0f;
        m[3][0] = m[3][1] = m[3][2] = 0.0f;
        m[3][3] = 1.0f;





    }

    void lookAt(Matrix4f& m,  Vector4& eye,Vector4& at,Vector4 &up){
        Vector4 xaxis, yaxis, zaxis;
        zaxis = at-eye;
        zaxis.normalize();
        xaxis = cross(up,zaxis);
        xaxis.normalize();
        yaxis = cross(zaxis,xaxis);

        m[0][0] = xaxis.x;
        m[1][0] = xaxis.y;
        m[2][0] = xaxis.z;
        m[3][0] = -(xaxis*eye);

        m[0][1] = yaxis.x;
        m[1][1] = yaxis.y;
        m[2][1] = yaxis.z;
        m[3][1] = -(yaxis*eye);

        m[0][2] = zaxis.x;
        m[1][2] = zaxis.y;
        m[2][2] = zaxis.z;
        m[3][2] = -(zaxis*eye);

        m[0][3] = m[1][3] = m[2][3] = 0.0f;
        m[3][3] = 1.0f;


    }

    void perspective(Matrix4f &m,float fovy, float aspect,float zn,float zf){
        float fax = 1.0f / (float)tan(fovy * 0.5f);
        m.setZero();
        m[0][0] = (float)(fax / aspect);
        m[1][1] = (float)(fax);
        m[2][2] = zf / (zf - zn);
        m[3][2] = - zn * zf / (zf - zn);
        m[2][3] = 1;
    }

    int check_cvv(const Vector4& v){
        float w = v.w;
        int check = 0;
        if (v.z < 0.0f) check |= 1;
        if (v.z >  w) check |= 2;
        if (v.x < -w) check |= 4;
        if (v.x >  w) check |= 8;
        if (v.y < -w) check |= 16;
        if (v.y >  w) check |= 32;
	    return check;
    }
}