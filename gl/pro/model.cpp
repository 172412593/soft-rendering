//
// Created by mnutec on 2021/2/1.
//

#include "model.h"

void GLM::model::draw(GLM::Graphic &graphic) {
    graphic.loadMatrix(m);
    graphic.VertexPointer(&mesh);
    graphic.drawElement(&indices);

}

void GLM::model::rotate(float theta, GLM::Vector4 v) {

    GLM::rotate(m,theta,v);

}

void GLM::model::translate(GLM::Vector4 v) {

    Matrix4f trans;
    GLM::translate(trans,v);
    m=m*trans;
}

void GLM::model::scale(GLM::Vector4 v) {
    Matrix4f sc;
    GLM::scale(sc,v);
    m=m*sc;
}
